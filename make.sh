gcc -Wno-format -o client client.c gtk.c else.c bot.c -Wno-deprecated-declarations -Wno-format-security -lm `pkg-config --cflags --libs gtk+-3.0` -export-dynamic