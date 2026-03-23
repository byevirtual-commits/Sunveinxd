FROM ubuntu:22.04

# Karşımıza çıkabilecek evet/hayırlı kurulum sorularını engellemek için
ENV DEBIAN_FRONTEND=noninteractive

# Gerekli derleme araçlarını indiriyoruz
RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    build-essential \
    git \
    libssl-dev \
    zlib1g-dev \
    libsodium-dev \
    libopus-dev

# Kodları sunucuya kopyalıyoruz
COPY . /app
WORKDIR /app

# CMake ile derleme işlemi (bot executable'ını oluşturur)
RUN cmake . && make -j$(nproc)

# İşlem bittiğinde oluşturulan botu başlat
CMD ["./bot"]
