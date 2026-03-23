FROM ubuntu:22.04
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y cmake g++ build-essential wget libssl-dev zlib1g-dev libsodium-dev libopus-dev
# D++ kütüphanesini DERLEMEK yerine, önceden hazırlanmış ZIP paketini anında YÜKLÜYORUZ.
# BU SAYEDE DONMA KESİNLİKLE OLUŞMAZ.
RUN wget -O dpp.deb https://github.com/brainboxdotcc/DPP/releases/download/v10.0.35/libdpp-10.0.35-linux-x64-deb.deb
RUN dpkg -i dpp.deb || apt-get install -f -y
COPY . /app
WORKDIR /app
RUN cmake . && make
CMD ["./bot"]
