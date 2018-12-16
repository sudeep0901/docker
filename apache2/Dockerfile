FROM ubuntu:latest

LABEL apache="Sudeep Patel"

# Install and run apache
RUN apt-get update && apt-get -y install  apache2 && apt-get clean

ENTRYPOINT ["/usr/sbin/apache2", "-k", "start"]

ENV APACHE_RUN_USER www-data
ENV APACHE_RUN_GROUP www-data
ENV APACHE_LOG_DIR /var/log/apache2

EXPOSE 80

# Copy site into place.
ADD app /var/www/site/app

# Update the default apache site with the config we created.
ADD apache-config.conf /etc/apache2/sites-enabled/000-default.conf

CMD /usr/sbin/apache2ctl -D FOREGROUND
