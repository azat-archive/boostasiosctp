
all: is_write_buffered

is_write_buffered: is_write_buffered.cpp
	g++ -I../../../../boost_1_38_0 -I../../.. -I../../../../boost_1_38_0/libs/asio/test -o is_write_buffered is_write_buffered.cpp -lboost_system-mt -lboost_thread-mt -lsctp

clean:
	rm -f is_write_buffered

