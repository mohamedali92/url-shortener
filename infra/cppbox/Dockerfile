FROM gcc

RUN apt-get -qq update
RUN apt-get -qq upgrade

RUN cd /usr/bin && mkdir gfortran && cd ../..

RUN apt-get -qq -y install gfortran

RUN apt-get -qq install cmake

RUN apt-get -qq install libboost-all-dev
RUN apt-get -qq install build-essential libtcmalloc-minimal4 && \
ln -s /usr/lib/libtcmalloc_minimal.so.4 /usr/lib/libtcmalloc_minimal.so


WORKDIR /usr/src

RUN git clone https://github.com/jtv/libpqxx.git \
--branch 6.4 --depth 1 \
&& cd libpqxx/ && mkdir build && cd build/ && cmake \
-DCMAKE_BUILD_TYPE=Release \
-DCMAKE_INSTALL_PREFIX=/usr/local \
-DPQXX_DIR=/usr/local/lib \
-DPostgreSQL_DIR=/usr/lib/x86_64-linux-gnu \
-DPQXX_TYPE_INCLUDE_DIR=/usr/local/include/pqxx \
-DPostgreSQL_TYPE_INCLUDE_DIR=/usr/include/postgresql \
-DCMAKE_MODULE_PATH=/usr/src/libpqxx-r6.4/cmake .. \
&& make && make install && ldconfig /usr/local/lib

RUN apt-get -qq install postgresql-server-dev-all
