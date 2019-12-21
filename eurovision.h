#ifndef EUROVISION_H_
#define EUROVISION_H_

#include <iostream>
using std::string;
using std::ostream;

enum VoterType { All, Regular, Judge };
enum Phase { Registration, Contest, Voting };

//---------------------------------------------------
/**
 * class Participant - contains all the participants information
 */
class Participant
{// relevant private members can be defined here, if necessary.
    string state_name;
    string song_name;
    int song_len;
    string singer_name;
    bool is_registered;

public :
    Participant(Participant& p) = delete;
    Participant& operator=(const Participant&) = delete;
    Participant(string state_name, string song_name, int song_len,
                string singer_name);
    Participant();
    //return state_name as a string
    string state() const;
    //return song_name as a string
    string song() const;
    //return singer_name as a string
    string singer() const;
    //return the song length
    int timeLength() const;
    /**
     * @return true if this participant is registered to a MainControl object
     * and false otherwise
     */
    bool isRegistered() const;
    /**
     * Update the participant characteristics.
     * @param new_song_name - if this param contain an empty string
     *                        the participant song_name wouldn't change
     * @param new_song_len - if this param contain an empty string
     *                        the participant song_name wouldn't change
     * @param new_singer_name - if this param equal's 0 the participant
     *                          song_length wouldn't change
     */
    void update(string new_song_name, int new_song_len,
                string new_singer_name);
    /**
     * Change the participant is_registered value to the condition
     * @param condition
     */
    void updateRegistered(bool condition);
};
//---------------------------------------------------
/**
 * Print the participant
 * example - [Israel/Song_Israel/175/Singer_Israel]
 * @param p
 * @return
 */
ostream& operator<<(ostream& os, const Participant& p);

/**
 * class Voter - contains a potential voter information
 */
class Voter
{
    string voter_state;
    enum VoterType voter_type;
    int num_of_votes;

public :
    Voter(string state_name);
    Voter(string state_name, enum VoterType voter_type);
    //return voter's state_name as a string
    string state() const;
    //return voter's VoterType as an enum
    enum VoterType voterType() const;
    //return how many times this voter voted
    int timesOfVotes() const;
    //add register another vote to this voter
    void operator++();
};
/**
 * Print the Voter
 * example - <Israel/Judge>
 * @param voter
 * @return
 */
ostream& operator<<(ostream& os, const Voter& voter);
// -----------------------------------------------------------
/**
 * struct Vote - contains a potential vote information
 */
struct Vote
{
    Voter& voter;
    string state_to_vote[10];
    Vote(Voter& voter, string state1, string state2="", string state3="",
            string state4="", string state5="", string state6="",
            string state7="", string state8="", string state9="",
            string state10="");
};
// -----------------------------------------------------------

/**
 * class MainControl - the main class of this eurovision management software,
 *                     contain all the contest information (participants, votes)
 */
class MainControl
{

    enum Phase phase;
    int max_song_len;
    int max_num_of_participants;
    int num_of_participants;
    int max_num_of_votes;
    /**
     * struct Result - contain all the participants information including vote
     *                 count.
     */
    struct Result{
        Participant* prt;
        /*
        string state_name;
        string song_name;
        int song_len;
        string singer_name;
        */
        int regular_score;
        int judge_score;
        Result* next_result;
    };
    //Result pointer for the first participant initialized as NULL
    Result* head;
    /**
     * @param state_name
     * @return pointer to the relevent Result that contain the same name
     *         as the param
     */
    Result* find_state(string state_name);
    /**
     * Remove n form the linked list
     * @param n
     */
    void remove_result(Result* n);
    /**
     * add a new result to the linked list sorted by state_name
     * @param n
     */
    void alphbetical_push(Result* n);
    /**
     * recursion function to delete the entire linked list
     * @param cur
     */
    static void deleteNodeReq(Result* cur);
    /**
     * print Result
     * example - [Israel/Song_Israel/175/Singer_Israel]
     * @param result
     * @return
     */
    friend ostream& operator<<(ostream& os, Result result);

public :
    /**
     * create an new MainControl object with the default values:
     * max_song_length  - 180
     * max_num_of_participants  - 26
     * max_num_of_votes - 5
     */
    MainControl();
    /**
     * create an new MainControl object with the current param's
     * 180, 26, 5);
     * @param max_song_length  - 180 by default
     * @param max_num_of_participants  - 26 by default
     * @param max_num_of_votes - the maximum num of votes a regular voter can make,
     *                           5 by default
     */
    MainControl(int max_song_length, int max_num_of_participants,
                int max_num_of_votes);
    ~MainControl();
    /**
     * change the phase of the contest only according to the correct order:
     * Registration->Contest->Voting
     * otherwise the function is ignored
     * @param new_phase
     */
    void setPhase(const enum Phase new_phase);
    /**
     * add a new participant to the contest
     * can't add participant if the current phase isn't Registration
     * @param p
     * @return the MainControl object to add multiple participants if necessary
     */
    MainControl& operator+=(Participant& p);
    /**
     * Delete a participant from the contest
     * can't delete participant if the current phase isn't Registration
     * @param p
     * @return the MainControl object to delete multiple participants
     *         if necessary
     */
    MainControl& operator-=(Participant& p);
    /**
     * @param p
     * @return true if p is a participant with legal state_name, song_name,
     *         singer_name and song_length and false other wise
     */
    bool legalParticipant(const Participant& p);
    /**
     * @param state_name
     * @return true if there is a participant registered to the contest with this state_name
     *         and false other wise
     */
    bool participate(const string& state_name);
    /**
     * add a vote to the contest
     * @param vote
     * @return the MainControl object to add multiple votes
     *         if necessary
     */
    MainControl& operator+=(const Vote& vote);
    /**
     * print the current contest according to the phase:
     * Registration - print all the registered participants information
     *                sorted by state_name
     * Contest - prints nothing but the phase name
     * Voting - print all the registered participants score status
     * @param main_control
     * @return
     */
    friend ostream& operator<<(ostream& os, const MainControl& main_control);

/*
================================================================================
                                    Part 2
================================================================================
 */

private:
    /**
    * class Compare - function class to compare between results according
     *                to certain criteria
    */
    class Compare{
        enum VoterType field_to_compare;
    public:
        Compare() = delete;
        explicit Compare(enum VoterType voter_type);
        /**
         * the compare function
         * @param res1
         * @param res2
         * @return return true if res1 is smaller then res2 according to
         *         a certain field, and false otherwise
         */
        bool operator()(Result* res1, Result* res2);
    };

public:
    /**
     * class ForwardIterator - iterator class of MainControl,
     *                         iterate's over the Results
     */
    class ForwardIterator{
        Result* data;
    public:
        ForwardIterator(Result* res = nullptr);
        ForwardIterator(const ForwardIterator& tmp_iter) = default;

        /**
         * advance the iterator forward
         * @return the new iterator
         */
        ForwardIterator& operator++ ();

        /**
         * @param tmp_iter
         * @return
         */
        ForwardIterator operator= (ForwardIterator& tmp_iter);

        /**
         * change the iterator data to the res param
         * @param res
         * @return
         */
        ForwardIterator operator= (Result* res);

        /**
         * compare between iterator according to their data
         * @param tmp_iter
         * @return true if the iterators points to the same Result and false
         *         otherwise
         */
        bool operator==(ForwardIterator tmp_iter);

        /**
         * compare between two iterators according to their state_name
         * @param tmp_iter
         * @return
         */
        bool operator<(ForwardIterator tmp_iter);

        /**
         *
         * @return the Result object of the iterator to access its content
         */
        Result& operator*();

        /**
         * conversion method from iterator to its data
         * @return
         */
        operator Result*() const ;
    };
    typedef ForwardIterator Iterator;
    /**
     * @return a Iterator object that points to the first Result
     */
    Iterator begin();
    /**
     * @return iterator object that points to NULL which is one node
     *         after the last node
     */
    Iterator end();

    /**
     * the function find the "place" winning participant in the contest
     * according to  a specific score calculation determined by
     * the voter_type param:
     * Regular - calculate according to Regular score only
     * Judge - calculate according to judge's score only
     * All - calculate according to judge's score and Regular score combined
     * example - main_control(2,Regular) - return the state name of the
     *           participant with the second best score according to
     *           Regular score only
     * @param place
     * @param voter_type
     * @return the relevant state name
     */
    string operator()(int place, enum VoterType voter_type);
};

#endif
