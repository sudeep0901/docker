FROM golang:alpine

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
RUN go build -o apiserver

# Expose port for service to be consumed
EXPOSE 8000

# Define entrypoint for container
ENTRYPOINT ["./apiserver"]
