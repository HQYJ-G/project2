
CFLAGS=-g -Wall
CC=arm-none-linux-gnueabi-gcc
AR=arm-none-linux-gnueabi-ar
RANLIB=arm-none-linux-gnueabi-ranlib
LIBS=-L./ -lcgic -I../inc
ROOTFS_DIR = /home/x/nfs/rootfs


OBJS = led.cgi
#OBJS += data_show.cgi
OBJS += fan.cgi
OBJS += buzzer.cgi

all: $(OBJS)

install: 
	cp *.cgi $(ROOTFS_DIR)/boa/cgi-bin/

libcgic.a: cgic.o cgic.h
	rm -f libcgic.a
	$(AR) rc libcgic.a cgic.o
	$(RANLIB) libcgic.a


$(OBJS): %.cgi:%.c libcgic.a
	$(CC) $< -o $@ ${LIBS}



clean:
	rm -f *.o *.a cgictest.cgi capture

