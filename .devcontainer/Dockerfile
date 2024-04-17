FROM ubuntu:latest

RUN apt update && apt upgrade -y

RUN apt install libreadline8 libreadline-dev -y

RUN apt install curl nano exa git wget lsb-release sudo build-essential -y

RUN apt install python3 -y && \
	apt install python3-pip -y

RUN apt install valgrind -y

RUN python3 -m pip install --upgrade pip setuptools && \
	python3 -m pip install norminette
