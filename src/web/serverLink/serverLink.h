#ifndef SERVER_LINK_H
#define SERVER_LINK_H

class ServerLink {

    private:
    // String basicLink = "devcontrol-backend.onrender.com";
    // String basicLink = "devcontrol.herokuapp.com";
    // String basicLink = "192.168.1.205:8000";
    String basicLink = "192.168.1.70:8000";

    bool isLocalIP(){
        return (basicLink.indexOf("192.168.") == 0);
    }

    String getHTTPlink(){
        if(isLocalIP()){
            return "http://" + basicLink + "/";
        }
        else{
            return "https://" + basicLink + "/";
        }
    }

    String getWSlink(){
        if(isLocalIP()){
            return "ws://" + basicLink;
        }
        else{
            return "wss://" + basicLink;
        }
    }

    public:
    const String httpLink;
    const String wsLink;

    ServerLink(): httpLink(getHTTPlink()), wsLink(getWSlink()) {}
};

#endif