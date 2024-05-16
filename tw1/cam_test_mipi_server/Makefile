CFLAGS = -Wall -o2 -g -std=gnu99 -pthread -I./include -DMYDBG
LDFLAGS = -lsqlite3 -ldl -ljpeg -lpthread
LDFLAGS = -ljpeg -lpthread


APP = server
SRCS	 = $(wildcard ./src/*.c)
OBJS	 = $(patsubst %.c, %.o,$(SRCS))

CC = gcc
#CC = arm-linux-gcc
all: $(APP)

$(APP): $(OBJS)
	$(CC) -o $(APP) $^ $(LDFLAGS)
	rm -f $(OBJS)
	
clean:
	rm -f $(OBJS) $(APP)
