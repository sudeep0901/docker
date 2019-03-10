FROM golang:alpine as build

# Add dependencies and create source directory
RUN apk add --no-cache git         && \
    go get github.com/gorilla/mux  && \
    apk del git                    && \
    mkdir -p $GOPATH/src/apiserver

# Set working directory
WORKDIR $GOPATH/src/apiserver

# Copy src into image
COPY ./src/ ./

# Build simple api server
RUN CGO_ENABLED=0 go build -installsuffix cgo -ldflags '-w -s' -o apiserver

FROM alpine

COPY --from=build /go/src/apiserver/apiserver /

# Expose port for service to be consumed
EXPOSE 80

# Define entrypoint for container
ENTRYPOINT ["./apiserver"]
