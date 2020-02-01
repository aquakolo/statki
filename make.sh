gcc -std=c11 -Wall -Wextra -ggdb -o client client.c gtk.c else.c bot.c -lm `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
chmod +x client