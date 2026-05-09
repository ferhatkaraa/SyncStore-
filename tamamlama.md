# Proje Tamamlama Durumu

## ✅ Yapılanlar (Yeşil)

- [x] **main.c dosyası oluşturuldu** - Fork ile child process'leri oluşturuyor
- [x] **child1.c dosyası oluşturuldu** - Parametre 1 kontrolü yapıyor
- [x] **child2.c dosyası oluşturuldu** - Parametre 2 kontrolü yapıyor  
- [x] **child3.c dosyası oluşturuldu** - Parametre 3 kontrolü yapıyor
- [x] **sinyal.c dosyası oluşturuldu** - Temel sinyal fonksiyonu mevcut
- [x] **storage.c dosyası oluşturuldu** - Semaphore ve paylaşımlı bellek fonksiyonları tam
- [x] **storage.h dosyası oluşturuldu** - Veri yapıları ve prototipler tanımlandı
- [x] **Tüm header dosyaları oluşturuldu** - child1.h, child2.h, child3.h, sinyal.h
- [x] **Include'lar düzeltildi** - Tüm dosyalarda storage.h eklendi
- [x] **README.md oluşturuldu** - Proje dokümantasyonu hazır

## ❌ Yapılmayanlar (Kırmızı)

- [ ] **Paylaşımlı bellek oluşturma** - main.c'de shmget() çağrısı eksik
- [ ] **Semaphore oluşturma** - main.c'de semget() çağrısı eksik
- [ ] **Paylaşımlı bellek bağlantısı** - Child'ler SharedData*'ya erişemiyor
- [ ] **Child'lerde storage kullanımı** - child1/2/3 fonksiyonları storage_write/read çağırmıyor
- [ ] **Parametre geçişi** - Child'ler semid ve SharedData parametrelerini almıyor
- [ ] **60 saniye çalışma süresi** - Child'ların 60 saniye boyunca çalışması sağlanmalı
- [ ] **Farklı periyotlar** - Child1: 2sn, Child2: 3sn, Child3: 4sn aralıklarla işlem yapmalı
- [ ] **PID tabanlı veri** - Child'lar kendi PID'lerini kullanarak veri yazmalı/okumalı
- [ ] **Hata kontrolü** - Paylaşımlı bellek ve semaphore hata kontrolleri eksik
- [ ] **Bellek temizleme** - Program sonunda shmctl() ve semctl() çağrıları yok
- [ ] **Sinyal geliştirmeleri** - 5 farklı sinyal için handler'lar eklenmeli

## 📋 Yapılması Gereken Adımlar

1. **main.c'de paylaşımlı bellek oluştur**
   ```c
   int shmid = shmget(IPC_PRIVATE, sizeof(SharedData), IPC_CREAT | 0666);
   SharedData *data = (SharedData*)shmat(shmid, NULL, 0);
   ```

2. **main.c'de semaphore oluştur**
   ```c
   int semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);
   semctl(semid, 0, SETVAL, 1);
   ```

3. **Child fonksiyonlarını güncelle**
   ```c
   void child1_function(int param, SharedData *data, int semid)
   ```

4. **Child'lerde storage fonksiyonlarını çağır**
   ```c
   storage_write(data, semid, "anahtar1", 100, getpid());
   ```

5. **60 saniye çalışma süresi ekle**
   ```c
   time_t start = time(NULL);
   while (time(NULL) - start < 60) {
       // 2/3/4 saniye aralıklarla işlem yap
       sleep(interval);
   }
   ```

6. **Sinyal handler'ları ekle**
   ```c
   signal(SIGINT, sigint_handler);
   signal(SIGTERM, sigterm_handler);
   signal(SIGUSR1, sigusr1_handler);
   signal(SIGUSR2, sigusr2_handler);
   signal(SIGHUP, sighup_handler);
   ```

7. **Program sonunda kaynakları temizle**
   ```c
   shmdt(data);
   shmctl(shmid, IPC_RMID, NULL);
   semctl(semid, 0, IPC_RMID);
   ```

## 🎯 Proje Mantığı
- Main process 3 child process fork'lar
- Her child kendi parametresine göre çalışır (1, 2, 3)
- Child'lar 60 saniye boyunca çalışır:
  - Child1: 2 saniyede bir okuma/yazma yapar
  - Child2: 3 saniyede bir okuma/yazma yapar  
  - Child3: 4 saniyede bir okuma/yazma yapar
- Child'ler kendi PID'lerini kullanarak veri yazma/okuma yapar
- Child'ler storage'daki kilitleme fonksiyonlarını kullanarak aynı anda yazma/okuma çakışmalarını engeller
- Paylaşımlı bellek üzerinden veri alışverişi yapılır
- 5 farklı sinyal için handler'lar program kontrolünü sağlar

## 🚨 Sinyal Geliştirme Önerileri
**sinyal.c** için eklenmesi gereken handler'lar:
1. **SIGINT (Ctrl+C)**: Programı güvenli şekilde sonlandırır, kaynakları temizler
2. **SIGTERM**: Kademeli kapatma işlemi yapar, child'ları durdurur
3. **SIGUSR1**: Child'lara durdurma/başlatma sinyali gönderir
4. **SIGUSR2**: İstatistikleri ekrana yazdırır (okuma/yazma sayıları)
5. **SIGHUP**: Konfigürasyon yeniden yükler (periyotları günceller)
