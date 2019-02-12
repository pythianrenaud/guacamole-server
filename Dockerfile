#
# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.
#
# Based on instructions from https://sourceforge.net/p/guacamole/discussion/1110834/thread/c7987fdb/

FROM centos:7.2.1511

RUN yum remove -y libguac libguac-client-rdp libguac-client-ssh libguac-client-vnc

# Build dependencies for guacd
RUN yum update -y && \
    yum groupinstall -y "Development tools" && \
    yum install -y git \
        cairo-devel libpng-devel uuid-devel pango-devel \
        libssh2-devel  pulseaudio-libs-devel libvorbis-devel \
        freerdp  freerdp-devel freerdp-plugins \
        libjpeg  libjpeg-devel \
        libwebp  libwebp-devel \
        libjpeg-turbo  uuid-devel \
        java-1.8.0-openjdk java-1.8.0-openjdk-headless java-1.8.0-openjdk-devel \
        libvncserver-devel libtelnet-devel

RUN mkdir /tmp/build

# Copy the current source dir into the build area
COPY . /tmp/guacamole-server/

# Build guacd  server from source
RUN cd /tmp/build && \
    cd /tmp/guacamole-server/ && \
    autoreconf -fi && \
    ./configure --with-init-dir=/etc/init.d --libdir=/usr/local/lib && \
    make && \
    make install && \
    ldconfig && \
    rm -rf /tmp/build

# Libraries have been installed in /usr/local/lib
RUN rm -rf /usr/lib64/freerdp/guac*

# Create new symlink to allow freeRDP and Guacamole to interface
RUN ln -s /usr/local/lib/freerdp/guac* /usr/lib64/freerdp/

# Expose the default listener port
EXPOSE 4822

# Start guacd, listening on port 0.0.0.0:4822
#
# Note the path here MUST correspond to the value specified in the
# PREFIX_DIR build argument.
#
CMD /usr/local/sbin/guacd -b 0.0.0.0 -L info -f
