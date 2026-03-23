import discord
import os
import asyncio

# Bot ayarları
intents = discord.Intents.default()
# Botun mesaj atabilmesi icin intents gerekli olabilir
bot = discord.Client(intents=intents)

TOKEN = os.getenv('TOKEN')
CHANNEL_IDS_STR = os.getenv('CHANNEL_IDS')
MESSAGE = os.getenv('MESSAGE')

if not TOKEN or not CHANNEL_IDS_STR or not MESSAGE:
    print("HATA: TOKEN, CHANNEL_IDS veya MESSAGE ortam degiskenleri eksik.")
    exit()

# Girilen kanal ID'lerini düzgün listeye çeviriyoruz
channel_ids = []
for cid in CHANNEL_IDS_STR.split(','):
    try:
        channel_ids.append(int(cid.strip()))
    except ValueError:
        pass

@bot.event
async def on_ready():
    print(f'Bot basariyla Discorda baglandi: {bot.user}')
    
    # Kanallara sırayla işlem yapıyoruz
    for cid in channel_ids:
        channel = bot.get_channel(cid) or await bot.fetch_channel(cid)
        if channel:
            try:
                await channel.send(MESSAGE)
                print(f"{cid} ID'li kanala mesaj gonderildi.")
            except Exception as e:
                print(f"{cid} ID'li kanala yetkim yok veya hata oldu: {e}")
        else:
            print(f"{cid} ID'li kanal bulunamadi (Botun sunucuda yetkisi yok).")
            
        # DİĞER KANALA GEÇMEDEN ÖNCE TAM 2 SANİYE BEKLE
        await asyncio.sleep(2) 
        
    print("Tum kanallara gonderim tamamlandi!")

bot.run(TOKEN)
