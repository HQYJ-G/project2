SEM_DIR = ./sem
ZIGBEE_DIR = ./zigbee
UART_DIR = ./uart
SQL_DIR = ./sql
INC_DIR = -I$(ZIGBEE_DIR) \
		  -I$(UART_DIR) \
		  -I$(SEM_DIR) \
		  -I$(SQL_DIR) \
		  -I./inc 
		  	
CROSS_COMPILE = arm-none-linux-gnueabi-
CC = $(CROSS_COMPILE)gcc
CFLAG = -g -Wall $(INC_DIR)

TARGET = main
OBJS = main.o
OBJS += $(ZIGBEE_DIR)/zigbee.o
OBJS += $(UART_DIR)/uart.o
OBJS += $(SEM_DIR)/sem.o
OBJS += $(SQL_DIR)/sqlite.o

all:$(TARGET)
	cp ./sem/sem.o ./cgi/
	make -C ./cgi/

$(TARGET):$(OBJS)
	$(CC) $^ -o $@ -lpthread -lsqlite3

$(OBJS):%.o:%.c
	$(CC) $(INC_DIR) -c $< -o $@ -lsqlite3


install:
	cp main /home/x/nfs/rootfs/project2/
	make install -C ./cgi/

clean:
	rm *.o
	rm $(TARGET)
	rm $(ZIGBEE_DIR)/*.o
	rm $(UART_DIR)/*.o
