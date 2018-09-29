FROM gcc
RUN apt-get update && apt-get install time
WORKDIR /build
COPY Makefile /build/
COPY crack.c /build/
RUN make && mv /build/crack.out /bin/
WORKDIR /
CMD time crack.out "$HASH" "$OMP_MAX_THREADS"
