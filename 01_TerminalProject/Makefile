DESTDIR=.

Show: Show.c
	cc $< -o $@ -lncursesw


install: Show
	install -D $< $(DESTDIR)/$< 

clean:
	rm -f *~ *.o Show a.out