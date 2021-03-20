FROM cppbox:latest

WORKDIR /usr/src/urlshortener
COPY . .

WORKDIR /usr/src/urlshortener/build
RUN cmake ../
RUN make
CMD ["./url_shortener"]
