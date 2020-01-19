// 35: Michał Antos (302815), Szymon Brożyna (309040)

#include "reports.hpp"

void generate_structure_report(const Factory& factory, std::ostream& os){
    os<<"\n";
    os<<"== LOADING RAMPS ==\n";
    os<<"\n";
    for(auto it = factory.ramp_cbegin(); it != factory.ramp_cend(); ++it){
        os<<"LOADING RAMP #"<<it->get_id()<<"\n  Delivery interval: "<<it->get_delivery_interval()<<"\n  Receivers:\n";
        for(auto &receiver : it->receiver_preferences_.get_preferences()){
            os<<"    "<<str_rep(receiver.first->get_receiver_type())<<" #"<<receiver.first->get_id()<<"\n";
        }
        os<<"\n";
    }
    os<<"\n";
//####################################
    os<<"== WORKERS ==\n";
    os<<"\n";
    for(auto it = factory.worker_cbegin(); it != factory.worker_cend(); ++it){
        os<<"WORKER #"<<it->get_id()<<"\n  Processing time: "<<it->get_processing_duration()<<"\n  Queue type: "<<
            str(it->get_queue()->get_queue_type())<<"\n  Receivers:\n";
        std::vector<std::pair<IPackageReceiver*,double>> sorte;
        for(auto &receiver : it->receiver_preferences_.get_preferences()){
            if(receiver.first->get_id() == 1){
                sorte.insert(sorte.begin(), receiver);
            }else{
                sorte.insert(sorte.end(), receiver);
            }
        }
        for(auto& elem : sorte) {
            os << "    " << str_rep(elem.first->get_receiver_type()) << " #" << elem.first->get_id() << "\n";
        }
        os<<"\n";
    }
    os<<"\n";
//####################################
    os<<"== STOREHOUSES ==\n";
    os<<"\n";
    for(auto it = factory.storehouse_cbegin(); it != factory.storehouse_cend(); ++it){
        os<<"STOREHOUSE #"<<it->get_id();
        os<<"\n";
        os<<"\n";
    }
//####################################
    os.flush();
}
void generate_simulation_turn_report(const Factory& factory, std::ostream& os, Time t){
    os<<"=== [ Turn: "<<t<<" ] ===\n";
    os<<"\n";
    os<<"== WORKERS ==\n";
    os<<"\n";
    for(auto it = factory.worker_cbegin(); it != factory.worker_cend(); ++it){
        os<<"WORKER #"<<it->get_id()<<"\n  PBuffer: ";
        if(it->get_processing_buffer()){
            os<<"#"<<it->get_processing_buffer()->get_id()<<" (pt = "<<it->get_package_processing_time(t)<<")";
        }else{
            os<<"(empty)";
        }
        os<<"\n  Queue: ";
        if((it->get_queue())->cbegin() != (it->get_queue())->cend() ) {
            for (auto &package: *it->get_queue()) {
                os << "#" << package.get_id() << ", ";
            }
            os.seekp(-2,os.cur);
        }else{
            os<<"(empty)";
        }

        os<<"\n  SBuffer: ";
        if(it->get_sending_buffer()){
            os<<"#"<<it->get_sending_buffer()->get_id()<<"\n";
        }else{
            os<<"(empty)\n";
        }
        os<<"\n";
    }
    os<<"\n";
//####################################
    os<<"== STOREHOUSES ==\n";
    os<<"\n";
    for(auto it = factory.storehouse_cbegin(); it != factory.storehouse_cend(); ++it){
        os<<"STOREHOUSE #"<<it->get_id();
        os<<"\n  Stock: ";
        if((it->get_queue())->cbegin() != (it->get_queue())->cend()){
            for(auto &package: *it->get_queue()){
                os<<"#"<<package.get_id()<<", ";
            }
            os.seekp(-2,os.cur);
        }else{
            os<<"(empty)";
        }
        os<<"\n";
    }

    os<<"\n";
//####################################
    os.flush();
}
