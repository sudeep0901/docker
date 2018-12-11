FROM microsoft/aspnetcore-build

LABEL author="Sudeep Patel"

ENV DOTNET_USE_POLLING_FILE_WATCHER=1
ENV ASPNETCORE_URLS=http://*:5000

WORKDIR /app
 
CMD ["/bin/bash", "-c", "dotnet restore && dotnet watch run"]