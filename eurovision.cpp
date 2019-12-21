#include <iostream>
#include <vector>
#include <algorithm>
#include "eurovision.h"
using std::string;
using std::ostream;
using std::endl;
using std::vector;
using std::sort;

template<typename Iterable, typename CmpFunction>
Iterable get(Iterable begin, Iterable end , int i, CmpFunction cmp);

/*
--------------------------------------------------------------------------------
                        Participant class implementation
--------------------------------------------------------------------------------
*/
Participant::Participant(string state_name, string song_name, int song_len,
                         string singer_name) {
    this->state_name = state_name;
    this->song_name = song_name;
    this->song_len = song_len;
    this->singer_name = singer_name;
    this->is_registered = false;
}

Participant::Participant() {
    this->state_name = "";
    this->song_name = "";
    this->song_len = 0;
    this->singer_name = "";
    this->is_registered = false;
}

string Participant::state() const {
    return this->state_name;
}

string Participant::song() const {
    return this->song_name;
}

string Participant::singer() const {
    return this->singer_name;
}

int Participant::timeLength() const {
    return this->song_len;
}

bool Participant::isRegistered() const {
    return this->is_registered;
}

void Participant::updateRegistered(bool condition) {
    this->is_registered = condition;
}

void Participant::update(string new_song_name, int new_song_len,
                         string new_singer_name) {
    if(this->isRegistered())
        return;
    if(new_song_name!=""){
        this->song_name = new_song_name;
    }
    if(new_song_len>0){
        this->song_len = new_song_len;
    }
    if(new_singer_name!=""){
        this->singer_name = new_singer_name;
    }
}

ostream& operator<<(ostream& os, const Participant& p){
    string str = "[" + p.state() + "/" + p.song() + "/";
       str+=std::to_string(p.timeLength());
       str+="/" + p.singer() + "]";
        return os << str;
}

/*
--------------------------------------------------------------------------------
                        Voter class implementation
--------------------------------------------------------------------------------
*/

Voter::Voter(string state_name) {
    this->voter_state = state_name;
    this->voter_type = Regular;
    this->num_of_votes = 0;
}

Voter::Voter(string state_name, enum VoterType voter_type){
    this->voter_state = state_name;
    this->voter_type = voter_type;
    this->num_of_votes = 0;
}

string Voter::state() const {
    return this->voter_state;
}

enum VoterType Voter::voterType() const {
    return this->voter_type;
}

int Voter::timesOfVotes() const {
    return this->num_of_votes;
}

void Voter::operator++() {
    this->num_of_votes++;
}

ostream& operator<<(ostream& os, const Voter& voter){
    string type;
    VoterType voter_type = voter.voterType();
    if(voter_type == Regular){
        type = "Regular";
    }
    if(voter_type == Judge){
        type = "Judge";
    }
    os<<"<"<<voter.state()<<"/"<<type<<">";
    return os;
}

/*
--------------------------------------------------------------------------------
                        Vote class implementation
--------------------------------------------------------------------------------
*/

Vote::Vote(Voter &voter, string state1, string state2, string state3,
           string state4, string state5, string state6,string state7,
           string state8, string state9, string state10): voter(voter){
    this->state_to_vote[0] = state1;
    if(this->voter.voterType()==Regular){
        for(int i=1; i<10; i++){
            this->state_to_vote[i] = "";
            }
        return;
    }
    this->state_to_vote[1] = state2;
    this->state_to_vote[2] = state3;
    this->state_to_vote[3] = state4;
    this->state_to_vote[4] = state5;
    this->state_to_vote[5] = state6;
    this->state_to_vote[6] = state7;
    this->state_to_vote[7] = state8;
    this->state_to_vote[8] = state9;
    this->state_to_vote[9] = state10;
}

/*
--------------------------------------------------------------------------------
                        MainControl class implementation
--------------------------------------------------------------------------------
*/

MainControl::MainControl() {
    this->phase = Registration;
    this->max_song_len = 180;
    this->max_num_of_participants = 26;
    this->num_of_participants = 0;
    this->max_num_of_votes = 5;
    this->head = NULL;
}

MainControl::MainControl(int max_song_length,
        int max_num_of_participants, int max_num_of_votes) {
    this->phase = Registration;
    this->max_song_len = max_song_length;
    this->max_num_of_participants = max_num_of_participants;
    this->num_of_participants = 0;
    this->max_num_of_votes = max_num_of_votes;
    this->head = NULL;
}

MainControl::~MainControl() {
    deleteNodeReq(this->head);
}

void MainControl::deleteNodeReq(MainControl::Result* cur) {
    if(!cur) return;
    deleteNodeReq(cur->next_result);
    cur->prt->updateRegistered(false);
    delete(cur);
}

void MainControl::setPhase(const enum Phase new_phase) {
    if(this->phase==Registration&&new_phase==Contest){
        this->phase= new_phase;
    }
    if(this->phase==Contest&&new_phase==Voting){
        this->phase= new_phase;
    }
}

MainControl::Result* MainControl::find_state(string state_name) {
    MainControl::Result* current = this->head;
    while(current){
        if(current->prt->state()==state_name){
            return current;
        }
        current = current->next_result;
    }
    return NULL;
}

void MainControl::remove_result(Result* n) {
    if(!n){
        return;
    }
    if(this->head == n)
    {
        this-> head = this->head->next_result;
        if(this->num_of_participants>0){
            this->num_of_participants--;
        }
        return;
    }
    Result* prev = head;
    while(prev->next_result != NULL && prev->next_result != n)
        prev = prev->next_result;
    if(prev->next_result == NULL){
        return;
    }
    prev->next_result = prev->next_result->next_result;
    if(this->num_of_participants>0) {
        this->num_of_participants--;
    }
}


void MainControl::alphbetical_push(Result* n)
{
    Result* prev = this->head;
    if(prev==NULL||prev->prt->state()>n->prt->state())
    {
        n->next_result=prev;
        this->head=n;
        return;
    }
    while(prev->next_result) {
        if(prev->next_result->prt->state() < n->prt->state())
            prev = prev->next_result;
        else{
            break;
        }
    }
    n->next_result=prev->next_result;
    prev->next_result=n;
}

MainControl& MainControl::operator+=(Participant &p) {
    if(this->phase!=Registration){
        return *this;
    }
    if(this->num_of_participants>=this->max_num_of_participants){
        return *this;
    }
    if(!legalParticipant(p)){
        return *this;
    }
    if(participate(p.state())){
        return *this;
    }
    Result* new_Result = new Result;
    new_Result->prt = &p;
    new_Result->regular_score=0;
    new_Result->judge_score=0;
    this->num_of_participants++;
    p.updateRegistered(true);
    alphbetical_push(new_Result);
    return *this;
}



MainControl& MainControl::operator-=(Participant &p) {
    if(this->phase!=Registration){
        return *this;
    }
    if(!p.isRegistered()){
        return *this;
    }
    Result* temp = find_state(p.state());
    remove_result(temp);
    delete(temp);
    p.updateRegistered(false);
    return *this;
}

bool MainControl::legalParticipant(const Participant& p){
    if(p.state()==""){
        return false;
    }
    if(p.song()=="") {
        return false;
    }
    if(p.timeLength()>max_song_len){
        return false;
    }
    if(p.singer()==""){
        return false;
    }
    return true;
}

bool MainControl::participate(const string& state_name){
    if(find_state(state_name)){
        return true;
    }
    return false;
}

MainControl& MainControl::operator+=(const Vote &vote) {
    Result* voted_state;
    if(this->phase!=Voting) return *this;
    if(!participate(vote.voter.state())) return *this;
    if((vote.voter).voterType()==Regular){
        if((vote.voter).timesOfVotes()>=this->max_num_of_votes){
            return *this;
        }
        if(!participate(vote.state_to_vote[0])){
            return *this;
        }
        if((vote.state_to_vote[0])==(vote.voter).state()){
            return *this;
        }
        (find_state(vote.state_to_vote[0]))->regular_score++;
        ++(vote.voter);
    }
    if((vote.voter).voterType()==Judge) {
        if ((vote.voter).timesOfVotes() >= 1) {
            return *this;
        }
        int score=12;
        bool all_votes_illegal= true;
        for(int i=0;i<10;i++){
            string curr=vote.state_to_vote[i];
            if(participate(curr)&&curr!=vote.voter.state()){
                voted_state=find_state(vote.state_to_vote[i]);
                voted_state->judge_score+=score;
                all_votes_illegal= false;
            }
            if(score>8){
                score-=2;
            }
            else {
                score--;
            }
        }
        if(!all_votes_illegal){
            ++vote.voter;
        }
    }
    return *this;
}

ostream &operator<<(ostream &os, MainControl::Result result) {
    os<<"["<<result.prt->state()<<"/";
    os<<result.prt->song()<<"/";
    os<<result.prt->timeLength()<<"/";
    os<<result.prt->singer()<<"]";
    return os;
}


ostream& operator<<(ostream& os, const MainControl& main_control){
    if(main_control.phase == Contest){
        return os<<"{"<<endl<<"Contest"<<endl<<"}"<<endl;
    }
    if(main_control.phase==Registration){
        MainControl::Result* current = main_control.head;
        os<<"{"<<endl<<"Registration"<<endl;
        while(current) {
            os<<*current<<endl;
            current = current->next_result;
        }
        os<<"}"<<endl;
    }
    if(main_control.phase==Voting){
        MainControl::Result* current = main_control.head;
        os<<"{"<<endl<<"Voting"<<endl;
        while(current) {
            os <<current->prt->state()<<" : Regular(";
            os<<current->regular_score<<") Judge(";
            os<<current->judge_score<<")"<<endl;
            current = current->next_result;
        }
        os<<"}"<<endl;
    }
    return os;
}

/*
================================================================================
                                    Part 2:
================================================================================
--------------------------------------------------------------------------------
                        Compare class implementation
--------------------------------------------------------------------------------
*/
MainControl::Compare::Compare(enum VoterType voter_type) {
    this->field_to_compare = voter_type;
}

bool MainControl::Compare::operator()(MainControl::Result* res1,
                                      MainControl::Result* res2) {
    if(field_to_compare == Regular){
        return res1->regular_score<res2->regular_score;
    }
    if(field_to_compare == Judge){
        return res1->judge_score<res2->judge_score;
    }
    if(field_to_compare == All){
        return (res1->regular_score + res1->judge_score) <
               (res2->regular_score + res2->judge_score);
    }
    return false;
}

/*
--------------------------------------------------------------------------------
                        Iterator class implementation
--------------------------------------------------------------------------------
*/

MainControl::ForwardIterator::ForwardIterator(MainControl::Result* res)
                                : data(res) {}

MainControl::ForwardIterator& MainControl::ForwardIterator::operator++ (){
    if(data!= nullptr){
        data = data->next_result;
    }
    return *this;
}

bool MainControl::ForwardIterator::operator==(ForwardIterator tmp_iter){
    return data == tmp_iter.data;
}

bool MainControl::ForwardIterator::operator<(ForwardIterator tmp_iter){
    if(tmp_iter.data != nullptr) {
        return data->prt->state() < tmp_iter.data->prt->state();
    }
    if(data == nullptr){
        return false;
    }
    return true;
}

MainControl::Result& MainControl::ForwardIterator::operator*(){
    return *data;
}

MainControl::ForwardIterator MainControl::ForwardIterator::operator=
        (MainControl::Result *res) {
    this->data = res;
    return *this;
}

MainControl::ForwardIterator MainControl::ForwardIterator::operator=
        (ForwardIterator& tmp_iter) {
    this->data = tmp_iter.data;
    return *this;
}

MainControl::ForwardIterator::operator Result*() const {
    return data;
}

//------------------------------------------------------------------------------
MainControl::Iterator MainControl::begin()  {
    return this->head;
}

MainControl::Iterator MainControl::end() {
    return nullptr;
}

string MainControl::operator()(int place, enum VoterType voter_type) {
    if(place>this->num_of_participants) {
        return "";
    }
    Compare cmp(voter_type);
    Iterator iter;
    iter = get(this->begin(), this->end(), place-1, cmp);
    return (*iter).prt->state();
}

template<typename Iterable, typename CmpFunction>
Iterable get(Iterable begin, Iterable end , int i, CmpFunction cmp){
    vector<Iterable> vec;
    for(Iterable I = begin; !(I==end); ++I){
        vec.push_back(I);
    }
    sort(vec.begin(), vec.end(), cmp);
    Iterable result = vec[vec.size()-1-i];
    return result;
}


