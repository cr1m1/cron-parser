cron-parser:
	g++ -o cron-parser main.cpp

test:
	g++ -o test parser_test.cpp

clean:
	rm -rf cron-parser
	rm -rf test