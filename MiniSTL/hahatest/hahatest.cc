/*
 * @Author: haha_giraffe
 * @Date: 2020-02-25 17:33:06
 * @Description: HAHATEST
 */
#include "hahatest.h"
#include <vector>
#include <map>

namespace HAHATEST{
    using std::cout;
    using std::endl;

inline std::vector<Test*>& gTest() {
    static std::vector<Test*> tests;
    return tests;
}

TestSaver::TestSaver(Test* test){
    gTest().push_back(test);
}

struct FailedMsg{
    FailedMsg(const char* f, int n, const std::string& s)
        :file(f), line(n), msg(s){ }
    
    const char* file;
    int line;
    std::string msg;
};

typedef std::map<std::string, std::vector<FailedMsg*>> CMap;
typedef std::map<std::string, CMap> TMap;

inline TMap& failed_tests() {
    static TMap m;
    return m;
}

void push_failed_msg(const std::string& test_name, const std::string& case_name, const char* file, int line, const std::string& msg){
    TMap& x = failed_tests();
    x[test_name][case_name].push_back(new FailedMsg(file, line, msg));
}

void run_all_test(){
    std::vector<Test*>& tests = gTest();
    int n = 0;
    for(auto i = 0; i < tests.size(); ++i){
        Test* test = tests[i];
        cout << "> begin test: " << test->name() << endl;
        test->run();
        cout << "< test " << test->name() << " done " << endl;
        ++n;

        delete test;
    }
    TMap& failed = failed_tests();
    if(failed.empty()){
        if(n > 0){
            cout << "\nCongratulations! All tests passed!" << endl;
        } else {
            cout << "Done nothing." << endl;
        }
    } else {
        size_t ntestfailed = failed.size();
        size_t ncasesfailed = 0;
        for(auto it = failed.begin(); it != failed.end(); ++it){
            CMap& cases = it->second;
            ncasesfailed += cases.size();
        }

        cout << "\n" << ncasesfailed << " case" << (ncasesfailed > 1 ? "s" : "");
        cout << " from " << ntestfailed << " test" << (ntestfailed > 1 ? "s" : "");
        cout << " failed. See details below:\n" << endl;

        for(auto it = failed.begin(); it != failed.end(); ++it){
            cout << "In test " << it->first << ":\n";

            CMap& cases = it->second;
            for(auto ct = cases.begin(); ct != cases.end(); ct++){
                cout << " case " << ct->first << ":\n";
                std::vector<FailedMsg*>& msgs = ct->second;
                for(auto i = 0; i < msgs.size(); ++i){
                    FailedMsg* msg = msgs[i];
                    cout << "  [" << msg->file << ":" << msg->line << "] " << msg->msg << "\n";
                    delete msg;
                }
            }

            cout.flush();
        }
    }    

}

}   //namespace HAHATEST
