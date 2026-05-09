# Sistem Projesi

## Proje Açıklaması
Bu proje, çoklu process'lerin paylaşımlı bellek üzerinde güvenli bir şekilde veri okuma ve yazma işlemlerini gerçekleştirmesini sağlayan bir sistemdir.

## Dosya Yapısı
- **main.c**: Ana program, fork ile child process'leri oluşturur
- **child1.c**: İlk child process, parametre 1 olduğunda çalışır
- **child2.c**: İkinci child process, parametre 2 olduğunda çalışır  
- **child3.c**: Üçüncü child process, parametre 3 olduğunda çalışır
- **sinyal.c**: Sinyal yönetimi için fonksiyonlar
- **storage.c**: Paylaşımlı bellek ve semaphore yönetimi
- **storage.h**: Veri yapıları ve fonksiyon prototipleri

## Sistem Mimarisi
1. **Main Process**: Child process'leri fork ile oluşturur
2. **Child Process'ler**: Kendi parametrelerine göre çalışır, storage fonksiyonlarını kullanır
3. **Storage Modülü**: 
   - Semaphore ile kilitleme/açma mekanizması
   - Paylaşımlı bellek yönetimi
   - Anahtar-değer çifti saklama

## Çalışma Zamanı ve Periyotlar
- **Tüm Child'lar**: 60 saniye boyunca çalışır
- **Child1**: 2 saniyede bir okuma/yazma işlemi yapar
- **Child2**: 3 saniyede bir okuma/yazma işlemi yapar  
- **Child3**: 4 saniyede bir okuma/yazma işlemi yapar
- **PID Kullanımı**: Her child kendi PID'ini yazma/okuma işlemlerinde kullanır

## Sinyal Yönetimi
**sinyal.c** için geliştirme önerileri:
1. **SIGINT (Ctrl+C)**: Programı güvenli şekilde sonlandırır
2. **SIGTERM**: Kademeli kapatma işlemi yapar
3. **SIGUSR1**: Child'lara durdurma/başlatma sinyali gönderir
4. **SIGUSR2**: İstatistikleri ekrana yazdırır
5. **SIGHUP**: Konfigürasyon yeniden yükler

## Güvenlik Mekanizması
- **Kilitleme (Semaphore)**: Aynı anda sadece bir process'in veriye erişmesini sağlar
- **Paylaşımlı Bellek**: Tüm process'lerin aynı veriye erişmesini sağlar
- **Senkronizasyon**: Yazma ve okuma işlemlerinin çakışmasını engeller

## Derleme ve Çalıştırma
```bash
gcc main.c child1.c child2.c child3.c sinyal.c storage.c -o program
./program
```

## Özellikler
- Çoklu process desteği
- Thread-safe veri erişimi
- Semaphore tabanlı senkronizasyon
- Anahtar-değer tabanlı depolama
