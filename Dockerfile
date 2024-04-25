FROM ubuntu

COPY . ./docker-files

WORKDIR /docker-files

RUN apt-get -y update && \
    apt-get -y install gcc && \
    rm -rf /var/lib/apt/lists/*

RUN gcc -o ./dgemm/chapter_3_v1 ./dgemm/chapter_3_v1.c ./dgemm/utils.c -lm -mavx

RUN gcc -o ./dgemm/chapter_3_v2 ./dgemm/chapter_3_v2.c ./dgemm/utils.c -lm -mavx

COPY . .