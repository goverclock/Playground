#include "tank_snd.h"

TankSound::TankSound() {
    select_snd.push_back(new QSound(":/sound/vgrssea.wav"));
    select_snd.push_back(new QSound(":/sound/vgrsseb.wav"));
    select_snd.push_back(new QSound(":/sound/vgrssec.wav"));
    
    move_snd.push_back(new QSound(":/sound/vgrsmoa.wav"));
    move_snd.push_back(new QSound(":/sound/vgrsmob.wav"));
    move_snd.push_back(new QSound(":/sound/vgrsmoc.wav"));

    attack_snd.push_back(new QSound(":/sound/vgrsata.wav"));
    attack_snd.push_back(new QSound(":/sound/vgrsatb.wav"));
    attack_snd.push_back(new QSound(":/sound/vgrsatc.wav"));
    attack_snd.push_back(new QSound(":/sound/vgrsatd.wav"));

    commander_snd.push_back(new QSound(":/sound/csof062.wav"));
    commander_snd.push_back(new QSound(":/sound/csof064.wav"));
}

void TankSound::play_select(int ind) {
    if(ind == -1) ind = rand() % select_snd.size();
    select_snd[ind]->play();
}

void TankSound::play_move(int ind) {
    if(ind == -1) ind = rand() % move_snd.size();
    move_snd[ind]->play();
}

void TankSound::play_attack(int ind) {
    if(ind == -1) ind = rand() % attack_snd.size();
    attack_snd[ind]->play();
}

void TankSound::play_commander(int ind) {
    if(ind == -1) ind = rand() % commander_snd.size();
    commander_snd[ind]->play();
}

