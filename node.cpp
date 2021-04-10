class node {
private:
    std::string curr;
    int times;
public:
    node(std::string currElm, int Times=0){
        curr= currElm;
        times=Times;
    }
};