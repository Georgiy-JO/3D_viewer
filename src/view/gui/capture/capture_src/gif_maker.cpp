#include "capture/gif_maker.h"
#include "third_party/gif.h"
#include <QDateTime>  // to generate time ralated file name
#include <stdexcept>
#include <QString>
#include <QDebug>
#define QIMAGE_SET_RGB


namespace gui::capture{

    GifMaker::GifMaker():Capturer(),m_recording(false),m_gif(std::make_unique<GifWriter>()){}
    /**
     * @note Why is it here you ask - simple, gif.h is a one header library (includes description
     * of the functions) and third party (aka should not be changed) - it really should better be
     * included included in .cpp file. But at the same time GifMaker (gif_maker.h) class needs to
     * know the structure GifWriter to work - forward declaration is the simplest way. At the  
     * same time unique_ptr in gif_maker.h really want to know how the destructor of GifWriter  
     * looks like (especially when gif_maker.h is included in another file) - forward declaration
     * is not enough for it. So we trick it by declaring destructor in gif_maker.h, even though 
     * it's just default. <(ꐦㅍ _ㅍ)>
     */
    GifMaker::~GifMaker()=default; 

    void GifMaker::Initialize (QPushButton* gif_button_){
        gif_button_->setText(kTypeList[m_active_type].type.data());
    }
    
    const std::string GifMaker::GetDefaultFileName() const{
        std::string file_name=kCaptureLocation;
        file_name+="/animation_";
        file_name+= QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss").toStdString();
        file_name+=kTypeList[m_active_type].tag;
        return file_name;
    }

    bool GifMaker::RecordGif(){
        SaveGif();
        if(!m_file_name.empty() && GifBegin(m_gif.get(), QString::fromStdString(m_file_name).toLatin1(), kDementions.width, kDementions.height, kFPS)){
            m_recording=true;
            return true;
        }
        return false;
    }
    bool GifMaker::RecordGif(const std::string& file_name_){
        return SetFileName(file_name_) && RecordGif();
    }

    bool GifMaker::RecordGif(const std::string& file_name_, const QImage& input_pic){
        if(m_recording && file_name_ == m_file_name)
            return RecordGif(input_pic);
        else
            return RecordGif(file_name_) && RecordGif(input_pic);
    }

    bool GifMaker::RecordGif(const QImage& input_pic){
        QImage img=input_pic.scaled(QSize(kDementions.width, kDementions.height));

        /**
         * @note Define QIMAGE_SET_RGB to convert images to BGR so gif.h could understand it.
         */
        #ifdef QIMAGE_SET_RGB
            std::vector<uint8_t> frame(kDementions.width * kDementions.height * 4);
            for (size_t y = 0; y < kDementions.height; ++y) {
            memcpy(
                frame.data() + y * kDementions.width * 4,
                img.constScanLine(y),
                kDementions.width * 4
            );
            }
            for (size_t i = 0; i < frame.size(); i += 4){
                std::swap(frame[i], frame[i + 2]);   // R <-> B
            }

            if(m_recording){
                return GifWriteFrame(m_gif.get(),frame.data(), kDementions.width, kDementions.height, kFPS);
            }
            else{
                return RecordGif() && GifWriteFrame(m_gif.get(),frame.data(), kDementions.width, kDementions.height, kFPS);
            }
        #else
            if(m_recording){
                return GifWriteFrame(m_gif.get(),img.bits(), kDementions.width, kDementions.height, kFPS);
            }
            else{
                return RecordGif() && GifWriteFrame(m_gif.get(),img.bits(), kDementions.width, kDementions.height, kFPS);
            }
        #endif
    }

    bool GifMaker::SaveGif(){
        if(m_recording){
            m_recording=false;
            return GifEnd(m_gif.get());
        }
        return false;
    }

    size_t GifMaker::GetFPS() const{
        return kFPS;
    }

    size_t GifMaker::GetTime() const{
        return kTime;
    }
    
} // gui::capture

