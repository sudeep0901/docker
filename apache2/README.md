docker run -d -p 80:80 -v /data/server/app:/var/www/site/app --name apache2 apache2

    https://bootstrap-it.com/encryption/


openssl req -nodes -days 10 -newkey rsa:2048 -keyout keyfile.pem -out certfile.pem

# verify generated certificate
openssl req -in certfile.pem -noout -verify -key keyfile.pem 
 
openssl req -in certfile.pem -noout -text


# Building own Ca certificate
sudeep@sudeep:~$ mkd
mkdir    mkdosfs  
sudeep@sudeep:~$ mkdir ~/my-ca
sudeep@sudeep:~$ cd my-ca/
sudeep@sudeep:~/my-ca$ ls
sudeep@sudeep:~/my-ca$ mkdir signedcerts private
sudeep@sudeep:~/my-ca$ echo '01' > serial
sudeep@sudeep:~/my-ca$ touch index.txt
sudeep@sudeep:~/my-ca$ 


create caconf file

vim caconfig.conf

export OPENSSL_CONF=~/my-ca/caconfig.conf


openssl req -x509 -newkey rsa:2048 -out cacert.pem -outform PEM -days 1825

openssl ca -in basereq.pem -out server_crt.pem

# apache2
sudo a2enmod ssl
sudo a2ensite default-ssl

cd /etc/apache2/sites-available/


