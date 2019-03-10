FROM golang:alpine as build

# Add dependencies and create source directory
RUN apk add --no-cache git         && \
    go get github.com/gorilla/mux  && \
    apk del git                    && \
    addgroup -S -g 500 api         && \
    adduser -S -u 500 -G api api   && \
    mkdir -p $GOPATH/src/apiserver

# Set working directory
WORKDIR $GOPATH/src/apiserver

# Copy src into image
COPY ./src/ ./

# Build simple api server
RUN CGO_ENABLED=0 go build -installsuffix cgo -ldflags '-w -s' -o apiserver

FROM scratch

COPY --from=build /go/src/apiserver/apiserver /
COPY --from=build /etc/passwd /etc/group /etc/

# Expose port for service to be consumed
EXPOSE 8000

# Set user as non-privileged alternative to root
USER api:api

# Define entrypoint for container
ENTRYPOINT ["./apiserver"]
