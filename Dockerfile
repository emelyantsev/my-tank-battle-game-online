FROM ubuntu:latest

RUN apt-get -y update
RUN apt-get -y install g++
RUN apt-get -y install libsfml-dev

COPY common_src /app/src/common_src
COPY server_src /app/src/server_src

WORKDIR /app/src/server_src

RUN g++ -c *cpp ../common_src/*.cpp -std=c++17  && g++ *.o -o ../../tanks_server -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lpthread -lsfml-network

WORKDIR /app

ENTRYPOINT ["./tanks_server"]
