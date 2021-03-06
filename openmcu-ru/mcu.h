
#ifndef _MCU_MCU_H
#define _MCU_MCU_H

#ifdef _WIN32
#pragma warning(disable:4786)
#endif

#include <ptlib.h>
#include <ptclib/httpsvc.h>
#include <ptclib/guid.h>

#ifdef _WIN32
#include <h323pluginmgr.h>
#endif

#ifdef __FreeBSD__
#  include <signal.h>
#endif

#include "config.h"

#include <map>
#include <h323.h>
#include <h323ep.h>
#include <h323rtp.h>
#include <h323pdu.h>
#include <h245.h>

#include "conference.h"
#include "filemembers.h"
#include "h323.h"
#include "sip.h"
#include "rtsp.h"
#include "reg.h"
#include "utils.h"
#include "recorder.h"
#include "mcu_caps.h"
#include "mcu_codecs.h"
#include "sockets.h"

#if USE_LIBYUV
#include <libyuv/scale.h>
#endif


#if P_SSL
#include <ptclib/shttpsvc.h>
typedef PSecureHTTPServiceProcess OpenMCUProcessAncestor;
#else
#include <ptclib/httpsvc.h>
typedef PHTTPServiceProcess OpenMCUProcessAncestor;
#endif

extern PHTTPServiceProcess::Info ProductInfo;

////////////////////////////////////////////////////////////////////////////////////////////////////

static const PString MCU_INTERNAL_CALL_PREFIX("INTERNAL_CALL_");

////////////////////////////////////////////////////////////////////////////////////////////////////

const WORD DefaultHTTPPort = 1420;

static const char ServerIdKey[]           = "OpenMCU-ru Server Id";
static const char LogLevelKey[]           = "Log Level";
static const char TraceLevelKey[]         = "Trace level";
static const char TraceRotateKey[]        = "Rotate trace files at startup";

static const char UserNameKey[]           = "Username";
static const char PasswordKey[]           = "Password";
static const char DisplayNameKey[]        = "Display name";

static PString EnableKey                  = "Enable";
static PString DisableKey                 = "Disable";
static PString EnableSelect               = "Enable,Disable";

static const char HttpIPKey[]             = "HTTP IP";
static const char HttpPortKey[]           = "HTTP Port";
static const char HttpLinkEventBufferKey[]= "Room control event buffer size";

static const char CallLogFilenameKey[]    = "Call log filename";

#if P_SSL
static const char HTTPSecureKey[]           = "Enable HTTP secure";
static const char HTTPCertificateFileKey[]  = "HTTP Certificate";
static PString DefaultHTTPCertificateFile   = PString(SYS_SSL_DIR)+PString(PATH_SEPARATOR)+"http.pem";
#endif

static const char RoomNameKey[]            = "Room";
static const char DefaultRoomKey[]         = "Default room";

static const char DefaultCallLogFilename[] = "mcu_log.txt"; 
static const char DefaultRoom[]            = "room101";
static const char AllowLoopbackCallsKey[]  = "Allow loopback calls";

static const char SipListenerKey[]         = "SIP Listener";

const unsigned int DefaultVideoFrameRate = 10;
const unsigned int DefaultVideoQuality   = 10;

static const char RecorderFfmpegDirKey[]   = "Video Recorder directory";
static const char RecorderResolutionKey[] = "Video Recorder resolution";
static const char RecorderFrameRateKey[]   = "Video Recorder frame rate";
static const char RecorderSampleRateKey[]  = "Video Recorder sound rate";
static const char RecorderAudioChansKey[]  = "Video Recorder sound channels";
static const char RecorderAudioCodecKey[]  = "Video Recorder audio codec";
static const char RecorderVideoCodecKey[]  = "Video Recorder video codec";
static const char RecorderVideoResolutionKey[] = "Video Recorder video resolution";
static const char RecorderAudioBitrateKey[] = "Video Recorder aduio bitrate";
static const char RecorderVideoBitrateKey[] = "Video Recorder video bitrate";
static const char RecorderDefaultAudioCodec[] = "ac3";
static const char RecorderDefaultVideoCodec[] = "mpeg4";

static const char VideoFrameWidthKey[]        = "Video frame width";
static const char VideoFrameHeightKey[]       = "Video frame height";
static const char VideoFrameRateKey[]         = "Video frame rate";
static const char AudioSampleRateKey[]        = "Audio sample rate";
static const char AudioChannelsKey[]          = "Audio channels";

#ifdef RECORDS_DIR
static const char DefaultRecordingDirectory[] = RECORDS_DIR;
#else
static const char DefaultRecordingDirectory[] = "records";
#endif
static const int  DefaultRecorderFrameWidth   = 704;
static const int  DefaultRecorderFrameHeight  = 576;
static const int  DefaultRecorderFrameRate    = 10;
static const int  DefaultRecorderSampleRate   = 16000;
static const int  DefaultRecorderAudioChans   = 1;

// room parameters
static const char ForceSplitVideoKey[]          = "Force split screen video";
static const char RoomAutoCreateKey[]           = "Auto create";
static const char RoomAutoCreateWhenConnectingKey[] = "Auto create when connecting";
static const char RoomAutoDeleteEmptyKey[]      = "Auto delete empty";
static const char RoomAutoRecordStartKey[]      = "Auto record start";
static const char RoomAutoRecordStopKey[]       = "Auto record stop";
static const char RoomAllowRecordKey[]          = "Allow record";
static const char RoomRecallLastTemplateKey[]   = "Recall last template";
static const char RoomTimeLimitKey[]            = "Room time limit";
static const char LockTemplateKey[]             = "Template locks conference by default";

static const char ReceivedVFUDelayKey[]         = "Received VFU delay";
static PString ReceivedVFUDelaySelect           = "Disable,0/0,5/5,5/10,10/5,10/10";
static const char SendVFUDelayKey[]             = "Send VFU delay";

static const char RTPInputTimeoutKey[]          = "RTP Input Timeout";
static PString RTPInputTimeoutSelect            = "Disable,15,30,60,120,300";
static const int  DefaultRTPInputTimeout        = 60;

static const char PingIntervalKey[]             = "Ping interval";
static PString PingIntervalSelect               = "Disable,20,30,40,50,60,120,180,240,300,600";

static const char AudioDeJitterKey[]            = "Audio de-jitter";

static PString DefaultConnectingWAVFile = PString(SYS_RESOURCE_DIR)+"/connecting.wav";
static PString DefaultEnteringWAVFile   = PString(SYS_RESOURCE_DIR)+"/entering.wav";
static PString DefaultLeavingWAVFile    = PString(SYS_RESOURCE_DIR)+"/leaving.wav";

static const char ConnectingWAVFileKey[]  = "Connecting WAV File";
static const char EnteringWAVFileKey[]    = "Entering WAV File";
static const char LeavingWAVFileKey[]     = "Leaving WAV File";

static const char InterfaceKey[]          = "H.323 Listener";
static const char GatekeeperUserNameKey[] = "Gatekeeper Username";
static const char GatekeeperAliasKey[]    = "Gatekeeper Room Names";
static const char GatekeeperTTLKey[]      = "Gatekeeper registration TTL(Time To Live)";
static const char GatekeeperPasswordKey[] = "Gatekeeper Password";
static const char GatekeeperModeKey[]     = "Gatekeeper Mode";
static const char GatekeeperKey[]         = "Gatekeeper";
static const char GatekeeperRetryIntervalKey[]    = "Gatekeeper request retry interval";
static const char DisableCodecsKey[]      = "Disable codecs - deprecated, use capability.conf instead!";
static const char NATRouterIPKey[]        = "NAT Router IP";
static const char NATTreatAsGlobalKey[]   = "Treat as global for NAT";
static const char NATStunServerKey[]      = "STUN server";
static const char NATStunListKey[]        = "STUN server list";
static const char DisableFastStartKey[]   = "Disable Fast-Start";
static const char DisableH245TunnelingKey[]="Disable H.245 Tunneling";
static const char RTPPortBaseKey[]        = "RTP Base Port";
static const char RTPPortMaxKey[]         = "RTP Max Port";
static const char DefaultProtocolKey[]    = "Default protocol for outgoing calls";

static const char RejectDuplicateNameKey[] = "Reject duplicate name";

static const char RtpProtoKey[]            = "RTP proto";
static PString RtpProtoSelect              = "RTP"
#if MCUSIP_SRTP
                                             ",SRTP,SRTP/RTP"
#endif
#if MCUSIP_ZRTP
                                             ",ZRTP"
#endif
                                             ;

static const char HostKey[]                = "Host";
static const char PortKey[]                = "Port";
static const char AddressKey[]             = "Address";
static const char ExpiresKey[]             = "Expires";
static const char TransportKey[]           = "Transport";
static const char AudioCodecKey[]          = "Audio codec";
static const char VideoCodecKey[]          = "Video codec";
static const char VideoResolutionKey[]     = "Video resolution";
static const char VideoFmtpKey[]           = "Video fmtp";
static const char BandwidthFromKey[]       = "Bandwidth from MCU";
static const char BandwidthToKey[]         = "Bandwidth to MCU";
static const char FrameRateFromKey[]       = "Frame rate from MCU";
static const char VideoCacheKey[]          = "Video cache";

static const char OPTION_FRAME_TIME[] = "Frame Time";
static const char OPTION_FRAME_RATE[] = "Frame Rate";
static const char OPTION_FRAME_WIDTH[] = "Frame Width";
static const char OPTION_FRAME_HEIGHT[] = "Frame Height";
static const char OPTION_MAX_BIT_RATE[] = "Max Bit Rate";
static const char OPTION_ENCODER_QUALITY[] = "Encoding Quality";
static const char OPTION_ENCODER_CHANNELS[] = "Encoder Channels";
static const char OPTION_DECODER_CHANNELS[] = "Decoder Channels";
static const char OPTION_TX_KEY_FRAME_PERIOD[] = "Tx Key Frame Period";

static PString MCUScaleFilterNames =
                                  "openmcu-ru built-in"
                                  ",libyuv|kFilterNone"
                                  ",libyuv|kFilterBilinear"
                                  ",libyuv|kFilterBox"
                                  ",swscale|SWS_FAST_BILINEAR"
                                  ",swscale|SWS_BILINEAR"
                                  ",swscale|SWS_BICUBIC"
                                  ",swscale|SWS_X"
                                  ",swscale|SWS_POINT"
                                  ",swscale|SWS_AREA"
                                  ",swscale|SWS_BICUBLIN"
                                  ",swscale|SWS_GAUSS"
                                  ",swscale|SWS_SINC"
                                  ",swscale|SWS_LANCZOS"
                                  ",swscale|SWS_SPLINE";

static const PTEACypher::Key CypherKey = {
  {
    103,  60, 222,  17, 128, 157,  31, 137,
    133,  64,  82, 148,  94, 136,   4, 209
  }
};

static PString MCUControlCodes = "NO ACTION,"
                                 "new action";

////////////////////////////////////////////////////////////////////////////////////////////////////

// All this silly stuff to get the plugins to load 
// because windows is stoopid and the pluginloader never gets instanced.
// This is required for ALL MFC based applications looking to load plugins!

#ifdef _WIN32
class PluginLoaderStartup2 : public PProcessStartup
{
  PCLASSINFO(PluginLoaderStartup2, PProcessStartup);
  public:
    void OnStartup()
    { 
      // load the actual DLLs, which will also load the system plugins
      PStringArray dirs = PPluginManager::GetPluginDirs();
      PPluginManager & mgr = PPluginManager::GetPluginManager();
      PINDEX i;
      for (i = 0; i < dirs.GetSize(); i++) 
        mgr.LoadPluginDirectory(dirs[i]);

      // now load the plugin module managers
      PFactory<PPluginModuleManager>::KeyList_T keyList = PFactory<PPluginModuleManager>::GetKeyList();
      PFactory<PPluginModuleManager>::KeyList_T::const_iterator r;
      for (r = keyList.begin(); r != keyList.end(); ++r) {
        PPluginModuleManager * mgr = PFactory<PPluginModuleManager>::CreateInstance(*r);
        if (mgr == NULL) {
          PTRACE(1, "PLUGIN\tCannot create manager for plugins of type " << *r);
        } else {
          PTRACE(3, "PLUGIN\tCreated manager for plugins of type " << *r);
          managers.push_back(mgr);
        }
      }
    }

    void OnShutdown()
    {
      while (managers.begin() != managers.end()) {
        std::vector<PPluginModuleManager *>::iterator r = managers.begin();
        PPluginModuleManager * mgr = *r;
        managers.erase(r);
        mgr->OnShutdown();
      }
    }

  protected:
    std::vector<PPluginModuleManager *> managers;
};
#endif //_WIN32

//////////////////////////////////////////////////////////////////////////////////////////////

class OpenMCUPreInit
{
  public:
    OpenMCUPreInit();

    ~OpenMCUPreInit()
    {
      delete pluginCodecManager;
    }

  protected:
    MCUPluginCodecManager *pluginCodecManager;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

class OpenMCU : public OpenMCUPreInit, public OpenMCUProcessAncestor
{
  PCLASSINFO(OpenMCU, OpenMCUProcessAncestor)

  public:
    OpenMCU();
    void Main();
    BOOL OnStart();
    void OnStop();
    void OnControl();
    void OnConfigChanged();
    BOOL Initialise(const char * initMsg);

    static OpenMCU & Current()
    { return (OpenMCU &)PProcess::Current(); }

    ConferenceManager * GetConferenceManager()
    { return manager; }

    MCUH323EndPoint & GetEndpoint()
    { return *endpoint; }

    MCUSipEndPoint * GetSipEndpoint()
    { return sipendpoint; }

    Registrar *GetRegistrar()
    { return registrar; };

    MCURtspServer *GetRtspServer()
    { return rtspServer; };

    const PString & GetServerId() const
    { return serverId; }

    const PString & GetDefaultRoomName() const
    { return defaultRoomName; }

    void LogMessage(const PString & str);
    void LogMessageHTML(PString str);

    int GetHttpBuffer() const { return httpBuffer; }

    virtual void HttpWrite_(PString evt) {
      httpBufferMutex.Wait();
      httpBufferedEvents[httpBufferIndex]=evt; httpBufferIndex++;
      if(httpBufferIndex>=httpBuffer){ httpBufferIndex=0; httpBufferComplete=1; }
      httpBufferMutex.Signal();
    }
    virtual void HttpWriteEvent(PString evt) {
      PString evt0; PTime now;
      evt0 += now.AsString("h:mm:ss. ", PTime::Local) + evt;
      HttpWrite_(evt0+"<br>\n");
      if(copyWebLogToLog) LogMessageHTML(evt0);
    }
    virtual void HttpWriteEventRoom(PString evt, PString room){
      PString evt0; PTime now;
      evt0 += room + "\t" + now.AsString("h:mm:ss. ", PTime::Local) + evt;
      HttpWrite_(evt0+"<br>\n");
      if(copyWebLogToLog) LogMessageHTML(evt0);
    }
    virtual void HttpWriteCmdRoom(PString evt, PString room){
      PStringStream evt0;
      evt0 << room << "\t<script>p." << evt << "</script>\n";
      HttpWrite_(evt0);
    }
    virtual void HttpWriteCmd(PString evt){
      PStringStream evt0;
      evt0 << "<script>p." << evt << "</script>\n";
      HttpWrite_(evt0);
    }
    virtual PString HttpGetEvents(int &idx, PString room){
      PStringStream result;
      while (idx!=httpBufferIndex){
        PINDEX pos=httpBufferedEvents[idx].Find("\t",0);
        if(pos==P_MAX_INDEX)result << httpBufferedEvents[idx];
        else if(room=="")result << httpBufferedEvents[idx].Mid(pos+1,P_MAX_INDEX);
        else if(httpBufferedEvents[idx].Left(pos)==room) result << httpBufferedEvents[idx].Mid(pos+1,P_MAX_INDEX);
        idx++;
        if(idx>=httpBuffer)idx=0;
      }
      return result;
    }
    virtual PString HttpStartEventReading(int &idx, PString room){
      PStringStream result;
      if(httpBufferComplete){idx=httpBufferIndex+1; if(idx>httpBuffer)idx=0;} else idx=0;
      while (idx!=httpBufferIndex){
        if(httpBufferedEvents[idx].Find("<script>",0)==P_MAX_INDEX){
          PINDEX pos=httpBufferedEvents[idx].Find("\t",0);
          if(pos==P_MAX_INDEX)result << httpBufferedEvents[idx];
          else if(room=="")result << httpBufferedEvents[idx].Mid(pos+1,P_MAX_INDEX);
          else if(httpBufferedEvents[idx].Left(pos)==room) result << httpBufferedEvents[idx].Mid(pos+1,P_MAX_INDEX);
        }
        idx++;
        if(idx>=httpBuffer)idx=0;
      }
      return result;
    }

    PString GetHtmlCopyright()
    {
      PStringStream html;
      html << "Copyright &copy;"
       << compilationDate.AsString("yyyy") << " by "
       << "<A HREF=\"" << copyrightHomePage << "\" target=\"_blank\"" << ">"
       << copyrightHolder;
      return html;
    }

#if MCU_VIDEO
    static VideoMixConfigurator vmcfg;

    virtual void RemovePreMediaFrame()
    { }

    virtual BOOL GetPreMediaFrame(void * buffer, int width, int height, PINDEX & amount)
    { return FALSE; }

    virtual BOOL GetEmptyMediaFrame(void * buffer, int width, int height, PINDEX & amount)
    { return GetPreMediaFrame(buffer, width, height, amount); }

    PString SetScaleFilterType(int type)
    {
      if(type < 0 || type > 14)
        type = 0;
#if !USE_LIBYUV
      if(type >= 1 && type <= 3)
        type = 4;
#endif
      scaleFilterType = type;
      return GetScaleFilterName(type);
    }

    int GetScaleFilterType()
    {
      return scaleFilterType;
    }

    static PString GetScaleFilterName(int type)
    {
      return MCUScaleFilterNames.Tokenise(",")[type];
    }

    static int GetScaleFilter(int type)
    {
      switch(type)
      {
#if USE_LIBYUV
        case(1):
          return libyuv::kFilterNone; // 0
        case(2):
          return libyuv::kFilterBilinear; // 1
        case(3):
          return libyuv::kFilterBox; // 2
#endif // USE_LIBYUV
#if USE_SWSCALE
        case(4):
          return SWS_FAST_BILINEAR; // 1
        case(5):
          return SWS_BILINEAR; // 2
        case(6):
          return SWS_BICUBIC; // 4
        case(7):
          return SWS_X; // 8
        case(8):
          return SWS_POINT; // 0x10
        case(9):
          return SWS_AREA; // 0x20
        case(10):
          return SWS_BICUBLIN; // 0x40
        case(11):
          return SWS_GAUSS; // 0x80
        case(12):
          return SWS_SINC; // 0x100
        case(13):
          return SWS_LANCZOS; // 0x200
        case(14):
          return SWS_SPLINE; // 0x400
#endif // USE_SWSCALE
        default:
          return 0;
      }
    }
#endif

#ifdef _WIN32
    // This is to get the plugins to load in MFC applications
    static void LoadPluginMgr() { plugmgr = new H323PluginCodecManager(); }
    static void RemovePluginMgr() { delete plugmgr; }
    static H323PluginCodecManager * plugmgr;
    static PluginLoaderStartup2 pluginLoader;
#endif

    // video recorder
    PString vr_ffmpegDir;
    unsigned vr_minimumSpaceMiB;

    const PString & GetLeavingWAVFile() const
    { return leavingWAVFile; }

    const PString & GetEnteringWAVFile() const
    { return enteringWAVFile; }

    const PString & GetConnectingWAVFile() const
    { return connectingWAVFile; }

    const PString & GetLogoFilename()
    {
      if(PFile::Exists(PString(SYS_CONFIG_DIR) + PATH_SEPARATOR + "logo.bmp"))
        logoFilename = "logo.bmp";
      else if(PFile::Exists(PString(SYS_CONFIG_DIR) + PATH_SEPARATOR + "logo.jpeg"))
        logoFilename = "logo.jpeg";
      else if(PFile::Exists(PString(SYS_CONFIG_DIR) + PATH_SEPARATOR + "logo.png"))
        logoFilename = "logo.png";
      else if(PFile::Exists(PString(SYS_CONFIG_DIR) + PATH_SEPARATOR + "logo.gif"))
        logoFilename = "logo.gif";
      else
        logoFilename = "";
      return logoFilename;
    }

    PMutex videoResizeDeltaTSCMutex;
    unsigned long videoResizeDeltaTSCSum;
    unsigned short videoResizeDeltaTSCCounter;
    time_t videoResizeDeltaTSCReportTime;

  protected:

    BOOL MCUHTTPListenerCreate(const PString & ip, unsigned port);
    void MCUHTTPListenerShutdown();
    void MCUHTTPListenerDelete();

    void InitialiseTrace();
    int currentLogLevel, currentTraceLevel;
    PString trace_section;
    BOOL traceFileRotated;
    PINDEX rotationLevel;
    PString logFilename;
    BOOL       copyWebLogToLog;

    void PrintOnStartInfo();

    PFilePath executableFile;
    ConferenceManager * manager;
    MCUH323EndPoint * endpoint;

    MCUSipEndPoint * sipendpoint;
    Registrar *registrar;
    MCURtspServer *rtspServer;

    PString    serverId;
    PString    defaultRoomName;
    BOOL       allowLoopbackCalls;

    PString connectingWAVFile;
    PString enteringWAVFile;
    PString leavingWAVFile;

    PString logoFilename;

    int        httpBuffer, httpBufferIndex;
    PStringArray httpBufferedEvents;
    BOOL       httpBufferComplete;

    PMutex     httpBufferMutex;

#if MCU_VIDEO
    int scaleFilterType;
#endif
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
class ExternalVideoRecorderThread : public PThread
{
  PCLASSINFO(ExternalVideoRecorderThread, PThread);
  public:
    ExternalVideoRecorderThread(PString roomName);

    void Main();
    BOOL running;
    PString fileName; // to replace %o
#ifdef _WIN32
    FILE *recordState;
#else
    pid_t recordPid;
#endif
};
*/
////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // _MCU_MCU_H
