pub enum Error {
    ChannelSendError(String),
    ChannelReceiveError(String),
    PoisonError(String),
    IOError(String),
}

impl std::string::ToString for Error {
    fn to_string(&self) -> String {
        match self {
            Error::ChannelSendError(err_str) => format!("ChannelSendError {}", err_str),
            Error::ChannelReceiveError(err_str) => format!("ChannelReceiveError {}", err_str),
            Error::PoisonError(err_str) => format!("PoisonError {}", err_str),
            Error::IOError(err_str) => format!("IOError {}", err_str),
        }
    }
}

impl<T> From<crossbeam::channel::SendError<T>> for Error
{
    fn from(value: crossbeam::channel::SendError<T>) -> Self {
        Error::ChannelSendError(value.to_string())
    }
}
impl<T> From<std::sync::PoisonError<T>> for Error
{
    fn from(value: std::sync::PoisonError<T>) -> Self {
        Error::PoisonError(value.to_string())
    }
}
impl From<std::io::Error> for Error
{
    fn from(value: std::io::Error) -> Self {
        Error::IOError(value.to_string())
    }
}
