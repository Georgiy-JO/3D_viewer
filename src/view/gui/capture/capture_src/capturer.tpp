#include <stdexcept>
#include <filesystem>
#include "capture/capturer.h"

namespace gui::capture{

    template <typename ChildClass>
    Capturer<ChildClass>::Capturer(){
        if(ChildClass::kTypeAmount<=0 || ChildClass::kTypeList.empty())
            throw std::runtime_error ("Constants set incorrectly!");
        m_active_type=0;
        m_file_name="";
        std::filesystem::create_directory(kCaptureLocation);
    }

    template <typename ChildClass>
    int Capturer<ChildClass>::GetActiveType() const{
        return m_active_type;
    }

    template <typename ChildClass>
    void Capturer<ChildClass>::SetActiveType(int type_){
        if(type_<ChildClass::kTypeAmount && type_>=0)
            m_active_type=type_;
    }

    template <typename ChildClass>
    const std::string Capturer<ChildClass>::GetTypeList() const{
        std::string output;
        for(int i=0, j=0;i<ChildClass::kTypeAmount;i++){
            output+=ChildClass::kTypeList[i].type;
            output+=" (";
            for(j=i; j<ChildClass::kTypeAmount && ChildClass::kTypeList[i].type==ChildClass::kTypeList[j].type;j++){
                if(i!=j) output+=" ";
                output+="*";
                output+=ChildClass::kTypeList[j].tag;
            }
            i=j-1;

            output+=")";
            if(ChildClass::kTypeAmount!=i+1) output+=";;";
        }
        return output;
    }

    template <typename ChildClass>
    const std::string& Capturer<ChildClass>::GetFileName() const{
        return m_file_name;
    }

    template <typename ChildClass>
    bool Capturer<ChildClass>::SetFileName(const std::string& file_name_){
        try{
            if(file_name_!=m_file_name)
                m_file_name=FixFileName(file_name_);
            return true;
        }
        catch(const std::exception& e){
            m_file_name="";
            return false;
        }
    }

    template <typename ChildClass>
    const std::string Capturer<ChildClass>::FixFileName(const std::string& file_name_) const{
        if(file_name_.empty())
            throw std::runtime_error ("File name is empty!");

        std::string local_file_name=file_name_;    
        int file_type=-1;
        for (int i=0;i<ChildClass::kTypeAmount;i++){
            if(local_file_name.ends_with(ChildClass::kTypeList[i].tag))
               file_type=i; 
        }
        if(file_type==-1) {
            file_type=m_active_type;
            local_file_name+=ChildClass::kTypeList[file_type].tag;
        }

        if(std::filesystem::exists(local_file_name)){
            std::string test_name=local_file_name;
            int i=0;
            while(true){
                test_name=local_file_name;
                i++;
                test_name.insert(test_name.rfind('.')," ("+std::to_string(i)+")");
                if(!std::filesystem::exists(test_name))
                    break;
            }
            local_file_name=test_name;
        }
        return local_file_name;
    }

} // gui::capture