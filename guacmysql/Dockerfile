FROM mysql:5.7

# fetch the guacamole db init scripts
ARG GUAC_REPO
ARG GUAC_MYSQL_VERSION
ARG BASE_URL=https://raw.githubusercontent.com/$GUAC_REPO/$GUAC_MYSQL_VERSION/extensions/guacamole-auth-jdbc/modules/guacamole-auth-jdbc-mysql/schema/
ADD ${BASE_URL}001-create-schema.sql /docker-entrypoint-initdb.d/
ADD ${BASE_URL}002-create-admin-user.sql /docker-entrypoint-initdb.d/

# the mysql docker image runs the .sh scripts in /docker-entrypoint-initdb.d
# this script will prefix the .sql files with "use guacamole_db;" so it uses the database we have defined
RUN echo 'sed -i "1i USE $MYSQL_DATABASE;" /docker-entrypoint-initdb.d/*.sql' > /docker-entrypoint-initdb.d/000-use-database.sh

# Change the permissions so everything can be modified and executed at runtime.
RUN chmod 777 -R /docker-entrypoint-initdb.d/