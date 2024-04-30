demo:main.c lcd.c ts.c font.c jpeg.c interface.c thread.c gif.c network.c
	arm-linux-gcc $^ -I ../include -L ./../lib -ljpeg -lfont -lm -g -pthread -o $@
clean:
	rm -rf demo