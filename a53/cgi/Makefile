
CFLAGS=-g -Wall
CC=arm-none-linux-gnueabi-gcc
AR=arm-none-linux-gnueabi-ar
RANLIB=arm-none-linux-gnueabi-ranlib
LIBS=-L./ -lcgic \
	 -lsqlite3 \
	 -I../inc \
	 -I../sem \
	 -I../sql
ROOTFS_DIR = /home/x/nfs/rootfs


OBJS = led.cgi
OBJS += fan.cgi
OBJS += buzzer.cgi
OBJS += log.cgi

all: $(OBJS) data_show.cgi

install: 
	cp *.cgi $(ROOTFS_DIR)/boa/cgi-bin/

libcgic.a: cgic.o cgic.h
	rm -f libcgic.a
	$(AR) rc libcgic.a cgic.o
	$(RANLIB) libcgic.a


$(OBJS): %.cgi:%.c libcgic.a
	$(CC) $< -o $@ ${LIBS}

data_show.cgi:data_show.c libcgic.a sem.o
	$(CC) $^ -o $@ ${LIBS}

clean:
	rm -f *.o *.a cgictest.cgi capture

