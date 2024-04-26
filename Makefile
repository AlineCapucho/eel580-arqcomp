compile-dgemm-v1:
	gcc -o ./dgemm/chapter_3_v1 ./dgemm/chapter_3_v1.c ./dgemm/utils.c -lm

compile-dgemm-v2:
	gcc -o ./dgemm/chapter_3_v2 ./dgemm/chapter_3_v2.c ./dgemm/utils.c -lm -march=native

docker-build:
	docker build -t dgemm .

docker-start:
	docker run -t -d dgemm