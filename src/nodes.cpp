//
// Created by MICHAŁ on 11.12.2019.
//
#include "nodes.hpp"

void ReceiverPreferences::add_receiver(IPackageReceiver *r) {
    //TODO:
    r += 0;
}

void ReceiverPreferences::remove_receiver(IPackageReceiver *r) {
    //TODO;
    r += 0;

}

IPackageReceiver *ReceiverPreferences::choose_receiver() {
    //TODO;
    return nullptr;
}

void PackageSender::send_package() {
    //std::vector<Package>::iterator ptr;
    //for (ptr = buffer.begin(); ptr = buffer.end(); ptr++) { //te referencje do r wartosc sie psuja
    //}
    for (Package& package : buffer){
        //auto probability = probability_generator_1();
        auto destiny = receiver_preferences_.choose_receiver();
        //TODO trzeba te paczki wyjebac jakos;
    }
    buffer.clear();
}
