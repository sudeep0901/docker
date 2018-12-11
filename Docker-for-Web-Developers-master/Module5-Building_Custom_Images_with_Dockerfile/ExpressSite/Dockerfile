FROM node:latest

LABEL author="Sudeep Patel"

ENV NODE_ENV=production 
ENV PORT=3000

WORKDIR   /var/www
COPY      . .

RUN       npm install

VOLUME ["/var/www"]

EXPOSE $PORT

ENTRYPOINT ["npm", "start"]