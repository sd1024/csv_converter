#MAKE Converter
CC=gcc
CLEAN=rm -f
PROGRAM_NAME=convertcsv
OBJECT_FILES=*.o
SOURCE_FILES=convert.c

$(PROGRAM_NAME): $(OBJECT_FILES)
	$(CC) -o $@ $^

$(OBJECT_FILES): $(SOURCE_FILES)
	$(CC) -c $^

clean:
	$(CLEAN) *.o $(PROGRAM_NAME)
