rm -rf a.out *.o
g++ -g httpclient.cpp test.cpp $(curl-config --libs)
