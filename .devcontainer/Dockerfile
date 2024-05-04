FROM --platform=$TARGETPLATFORM mcr.microsoft.com/devcontainers/ruby:2.7-bullseye

# add apt sources for llvm
RUN curl -fsSL https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add -
RUN echo "deb http://apt.llvm.org/bullseye/ llvm-toolchain-bullseye-17 main" >> /etc/apt/sources.list.d/llvm.list
RUN apt-get update --fix-missing && apt-get -y upgrade

# install dependencies
RUN apt-get install -y wget gnupg gnupg2 gdb autoconf automake autotools-dev libtool

# install & alias llvm tools
RUN apt-get install -y --no-install-recommends \
	clang-17 \
	clangd-17 \
    clang-format-17 \
    clang-tidy-17
RUN ln -s /usr/bin/clang-format-17 /usr/local/bin/clang-format
RUN ln -s /usr/bin/clang-tidy-17 /usr/local/bin/clang-tidy
RUN ln -s /usr/bin/clang-17 /usr/bin/clang
RUN ln -s /usr/bin/clangd-17 /usr/bin/clangd

# install ceedling for testing
RUN gem install ceedling --no-user-install
ADD https://sourceware.org/pub/valgrind/valgrind-3.22.0.tar.bz2 /opt/src/valgrind-3.22.0.tar.bz2
RUN cd /opt/src && tar -xvf valgrind-3.22.0.tar.bz2 && \
	cd /opt/src/valgrind-3.22.0 && ./autogen.sh && ./configure && make && make install

# install additional tools...
RUN apt-get install -y libreadline-dev
RUN	git config --global --add safe.directory /workspaces/c-dev/minishell
RUN sudo touch /etc/apt/sources.list.d/devdep.list
RUN echo 'deb http://ftp.de.debian.org/debian bullseye main' | sudo tee -a /etc/apt/sources.list.d/devdep.list
RUN apt-get update -y
RUN apt-get install -y bear libclang-rt-17-dev-dbgsym clang-tools-17 libllvm17 llvm-17 llvm-17-dev llvm-17-runtime \
		libclang-common-17-dev libclang-17-dev libclang1-17 libfuzzer-17-dev libclang-rt-17-dev
RUN ln -s /usr/bin/llvm-symbolizer-17 /usr/local/bin/llvm-symbolizer

RUN python3 -m pip install --upgrade pip setuptools
RUN python3 -m pip install norminette
