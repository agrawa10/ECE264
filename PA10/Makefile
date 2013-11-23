GCC = gcc
CFLAGS = -g -Wall -Wshadow
OBJS = pa10.o tree.o answer10.o
HDRS = pa10.h tree.h
TARGET = pa10
VALGRIND = valgrind --tool=memcheck --leak-check=full --verbose

.PHONY: test clean environment test_shapes1 test_shapes2 test_shapes3 test_shapes4 test_shapes5 test_shapes6 test_shapes7 test_shapes8 test_shapes9

pa10: $(OBJS) $(HDRS)
	$(GCC) $(CFLAGS) $(OBJS) -o $@

testall: | test_shapes1 test_shapes2 test_shapes3 test_shapes4 test_shapes5 test_shapes6 test_shapes7 test_shapes8 test_shapes9

test_shapes1: $(TARGET) | environment
	./$(TARGET) shapes 1 > outputs/shapes-1
	diff expected/shapes-1 outputs/shapes-1
	$(VALGRIND) --log-file=outputs/memoutput_shapes-1 ./pa10 shapes 1 >/dev/null
	@bin/valgrind-checker.sh outputs/memoutput_shapes-1

test_shapes2: $(TARGET) | environment
	./$(TARGET) shapes 2 > outputs/shapes-2
	diff expected/shapes-2 outputs/shapes-2
	$(VALGRIND) --log-file=outputs/memoutput_shapes-2 ./pa10 shapes 2 >/dev/null
	@bin/valgrind-checker.sh outputs/memoutput_shapes-2

test_shapes3: $(TARGET) | environment
	./$(TARGET) shapes 3 > outputs/shapes-3
	diff expected/shapes-3 outputs/shapes-3
	$(VALGRIND) --log-file=outputs/memoutput_shapes-3 ./pa10 shapes 3 >/dev/null
	@bin/valgrind-checker.sh outputs/memoutput_shapes-3

test_shapes4: $(TARGET) | environment
	./$(TARGET) shapes 4 > outputs/shapes-4
	diff expected/shapes-4 outputs/shapes-4
	$(VALGRIND) --log-file=outputs/memoutput_shapes-4 ./pa10 shapes 4 >/dev/null
	@bin/valgrind-checker.sh outputs/memoutput_shapes-4

test_shapes5: $(TARGET) | environment
	./$(TARGET) shapes 5 > outputs/shapes-5
	diff expected/shapes-5 outputs/shapes-5
	$(VALGRIND) --log-file=outputs/memoutput_shapes-5 ./pa10 shapes 5 >/dev/null	
	@bin/valgrind-checker.sh outputs/memoutput_shapes-5

test_shapes6: $(TARGET) | environment
	./$(TARGET) shapes 6 > outputs/shapes-6
	diff expected/shapes-6 outputs/shapes-6
	$(VALGRIND) --log-file=outputs/memoutput_shapes-6 ./pa10 shapes 6 >/dev/null
	@bin/valgrind-checker.sh outputs/memoutput_shapes-6

test_shapes7: $(TARGET) | environment
	./$(TARGET) shapes 7 > outputs/shapes-7
	diff expected/shapes-7 outputs/shapes-7
	$(VALGRIND) --log-file=outputs/memoutput_shapes-7 ./pa10 shapes 7 >/dev/null
	@bin/valgrind-checker.sh outputs/memoutput_shapes-7

test_shapes8: $(TARGET) | environment
	./$(TARGET) shapes 8 > outputs/shapes-8
	diff expected/shapes-8 outputs/shapes-8
	$(VALGRIND) --log-file=outputs/memoutput_shapes-8 ./pa10 shapes 8 >/dev/null
	@bin/valgrind-checker.sh outputs/memoutput_shapes-8

test_shapes9: $(TARGET) | environment
	./$(TARGET) shapes 9 > outputs/shapes-9
	diff expected/shapes-9 outputs/shapes-9
	$(VALGRIND) --log-file=outputs/memoutput_shapes-9 ./pa10 shapes 9 >/dev/null
	@bin/valgrind-checker.sh outputs/memoutput_shapes-9

environment:
	@mkdir -p outputs

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

clean:
	rm -r $(TARGET) $(OBJS) outputs/*
