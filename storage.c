#include "storage.h"
#include <stdio.h>
#include <string.h>
#include <sys/sem.h>

// --- KALEMİ AL (KİLİTLE) ---
void kilitle(int semid) {
    // İşletim sistemine diyoruz ki: "Kalemi alacağım, eğer kalem başkasındaysa beni burada beklet."
    struct sembuf operasyon = {0, -1, 0}; 
    semop(semid, &operasyon, 1);
}

// --- KALEMİ BIRAK (KİLİDİ AÇ) ---
void kilidi_ac(int semid) {
    // İşletim sistemine diyoruz ki: "İşim bitti, kalemi masaya bırakıyorum, bekleyen varsa gelsin."
    struct sembuf operasyon = {0, 1, 0};
    semop(semid, &operasyon, 1);
}

// --- VERİ YAZMA ---
void storage_write(SharedData *data, int semid, char *key, int value, int child_id) {
    kilitle(semid); // Kapıyı kilitledim, içeri girdim.

    // Deftere (belleğe) yazma işlemi
    strcpy(data->db[0].key, key);
    data->db[0].value = value;
    printf("Child %d: Deftere yazdim: %s = %d\n", child_id, key, value);

    kilidi_ac(semid); // Kapıyı açtım, çıktım.
}

// --- VERİ OKUMA ---
int storage_read(SharedData *data, int semid, char *key, int child_id) {
    kilitle(semid); // Kapıyı kilitledim, içeri girdim.

    // Defterden (bellekten) okuma işlemi
    int okunan_deger = data->db[0].value;
    printf("Child %d: Defterden okudum, deger: %d\n", child_id, okunan_deger);

    kilidi_ac(semid); // Kapıyı açtım, çıktım.
    return okunan_deger;
}