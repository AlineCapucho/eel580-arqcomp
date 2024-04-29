compile-dgemm-v1:
	gcc -o ./dgemm/chapter_3_v1 ./dgemm/chapter_3_v1.c ./dgemm/utils.c

compile-dgemm-v2:
	gcc -mavx -o ./dgemm/chapter_3_v2 ./dgemm/chapter_3_v2.c ./dgemm/utils.c

compile-dgemm-v3:
	gcc -mavx -o ./dgemm/chapter_4_v3 ./dgemm/chapter_4_v3.c ./dgemm/utils.c

compile-dgemm-v4:
	gcc -mavx -o ./dgemm/chapter_5_v4 ./dgemm/chapter_5_v4.c ./dgemm/utils.c

docker-build:
	docker build -t dgemm .

docker-start:
	docker run -t -d dgemm