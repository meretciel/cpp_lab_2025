#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

/*** define ***/
#define CTRL_KEY(k) ((k) & 0x1f)
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/*** data ***/

struct editorConfig {
    int cx;
    int cy;
    int screenrows;
    int screencols;
    struct termios orig_termios;
};
struct editorConfig E;



enum EditorKey {
    CTRL_Q = CTRL_KEY('q'),
    ARROW_LEFT = 1000,
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN,
    PAGE_UP,
    PAGE_DOWN,
    DELETE,

};


/*** terminal ***/
void die(const char *s) {
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
    perror(s);
    exit(1);
}

void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios) == -1)
        die("tcsetattr");
}

void enableRawMode() {
    if (tcgetattr(STDIN_FILENO, &E.orig_termios) == -1) die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = E.orig_termios;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

/**
 * Reads a key press or a key press sequence from the stdin.
 *
 * @return The EditorKey enum.
 */
int editorReadKey(FILE *fp) {
    int nread;
    char c;
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        if (nread == -1 && errno != EAGAIN) die("read");
    }

    if (c == '\x1b')
    {
        fprintf(fp, "Detect the start of escape sequence.\n");

        char seq[3];
        if (read(STDIN_FILENO, &seq[0], 1) != 1) return '\x1b';
        if (read(STDIN_FILENO, &seq[1], 1) != 1) return '\x1b';

        if (seq[0] == '[')
        {

            if ('A' <= seq[1] && seq[1] <= 'D')
            {
                switch (seq[1])
                {
                    case 'A': return ARROW_UP;
                    case 'B': return ARROW_DOWN;
                    case 'C': return ARROW_RIGHT;
                    case 'D': return ARROW_LEFT;
                    default: return '\x1b';
                }

            } else if ('1' <= seq[1] && seq[1] <= '9')
            {
                if (read(STDIN_FILENO, &seq[2], 1) != 1) return '\x1b';
                if (seq[2] == '~')
                {
                    switch (seq[1])
                    {
                        case '3': return DELETE;
                        case '5': return PAGE_UP;
                        case '6': return PAGE_DOWN;
                        default: return '\x1b';

                    }
                } else
                {
                    return '\x1b';
                }
            } else
            {
                return '\x1b';
            }

        } else
        {
            return '\x1b';
        }

    } else
    {
        return c;
    }


}

int getWindowSize(int *rows, int *cols) {
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
        return -1;
    } else {
        *cols = ws.ws_col;
        *rows = ws.ws_row;
        return 0;
    }
}


/*** append buffer ***/
struct abuf {
    char *b;
    int len;
};

#define ABUF_INIT {NULL, 0}

void abAppend(struct abuf *ab, const char *s, int len) {
    char *new = realloc(ab->b, ab->len + len);
    if (new == NULL) return;
    memcpy(&new[ab->len], s, len);
    ab->b = new;
    ab->len += len;
}
void abFree(struct abuf *ab) {
    free(ab->b);
}

/*** cursor ***/

void moveCursorLeft() {
    E.cx--;
    E.cx = MAX(0, E.cx - 1);
}

void moveCursorRight() {
    E.cx = MIN(E.screencols - 1, E.cx + 1);
}

void moveCursorDown() {
    E.cy = MIN(E.screenrows - 1, E.cy + 1);
}

void moveCursorUp() {
    E.cy = MAX(0, E.cy - 1);
}

void pageDown() {
    int times = E.screenrows;
    while (times--)
    {
        moveCursorDown();
    }
}

void pageUp() {
    int times = E.screenrows;
    while (times--)
    {
        moveCursorUp();
    }
}

void delete() {

}

void resetCursorTopLeft() {
    write(STDOUT_FILENO, "\x1b[H", 3);
}

/*** screen ***/
void clearScreen() {
    write(STDOUT_FILENO, "\x1b[2J", 4);
}

int getCursorPosition(int *rows, int *cols) {
    char buf[32];
    unsigned int i = 0;
    if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4) return -1;
    while (i < sizeof(buf) - 1) {
        if (read(STDIN_FILENO, &buf[i], 1) != 1) break;
        if (buf[i] == 'R') break;
        i++;
    }
    buf[i] = '\0';
    if (buf[0] != '\x1b' || buf[1] != '[') return -1;
    if (sscanf(&buf[2], "%d;%d", rows, cols) != 2) return -1;
    return 0;
}

/*** input ***/

void editorProcessKeypress(FILE *fp) {
    int c = editorReadKey(fp);
    switch (c) {
        case CTRL_Q:
            clearScreen();
            resetCursorTopLeft();
            fclose(fp);
            exit(0);
            break;
        case ARROW_UP: moveCursorUp(); break;
        case ARROW_DOWN: moveCursorDown(); break;
        case ARROW_LEFT: moveCursorLeft(); break;
        case ARROW_RIGHT: moveCursorRight(); break;
        case PAGE_DOWN: pageDown(); break;
        case PAGE_UP: pageUp(); break;
        case DELETE: delete(); break;
        default: return;
    }
}

/*** output ***/
void editorDrawRows(struct abuf *ab) {
    for (int y = 0; y < E.screenrows; y++) {
        abAppend(ab, "\x1b[K", 3);  // clear the current line
        abAppend(ab, "~", 1);
        if (y < E.screenrows - 1) {
            abAppend(ab, "\r\n", 2);
        }
    }
}

void editorRefreshScreen() {
    struct abuf ab = ABUF_INIT;
    abAppend(&ab, "\x1b[?25l", 6); // hide cursor
    abAppend(&ab, "\x1b[H", 3);   // reset cursor to top-left
    editorDrawRows(&ab);
    char buf[32];
    snprintf(buf, sizeof(buf), "\x1b[%d;%dH", E.cy + 1, E.cx + 1);
    abAppend(&ab, buf, strlen(buf));

    abAppend(&ab, "\x1b[?25h", 6); // re-activate cursor
    write(STDOUT_FILENO, ab.b, ab.len);
    abFree(&ab);
}

/*** init ***/
void initEditor() {
    E.cx = 0;
    E.cy = 0;
    if (getWindowSize(&E.screenrows, &E.screencols) == -1) die("getWindowSize Failed.");
}

int main() {
    FILE *fp = fopen("/home/ryan/workspace/tmp/editor.log", "w");
    if (fp == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    enableRawMode();
    initEditor();
    editorRefreshScreen();
    while (1) {
        editorProcessKeypress(fp);
        editorRefreshScreen();
        fflush(fp);
    }

    return 0;
}