#pragma once

#include <QSound>
#include <QVector>

class TankSound {
   public:
    TankSound();
    void play_select(int ind = -1);
    void play_move(int ind = -1);
    void play_attack(int ind = -1);
    void play_commander(int ind = -1);

   private:
    QVector<QSound*> select_snd;    // vgrssex
    QVector<QSound*> move_snd;    // vgrsmox
    QVector<QSound*> attack_snd;  // vgrsatx
    QVector<QSound*> commander_snd;     // 
};
