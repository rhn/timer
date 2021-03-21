/*! Async communication between the work thread and the UI thread */
use once_cell::sync::Lazy;
use std::sync::Mutex;
use std::sync::mpsc::{ channel, Receiver, Sender };


enum Bus<T> {
    Unclaimed(Receiver<T>, Sender<T>),
    Claimed(Sender<T>),
    Empty,
}

impl<T> Bus<T> {
    fn claim(&mut self) -> Option<Receiver<T>> {
        use Bus::*;
        let mut recv = None;
        *self = match std::mem::replace(self, Empty) {
            Unclaimed(r, s) => {
                recv = Some(r);
                Claimed(s)
            },
            Claimed(s) => Claimed(s),
            _ => panic!(),
        };
        recv
    }
    fn get_sender(&self) -> Sender<T> {
        use Bus::*;
        match self {
            Unclaimed(_, s) => s.clone(),
            Claimed(s) => s.clone(),
            _ => panic!(),
        }
    }
}

static BUS: Lazy<Mutex<Bus<Message>>> = Lazy::new(|| {
    let (s, r) = channel();
    Mutex::new(Bus::Unclaimed(r, s))
});


pub enum Message {
    TotalChanged(u32),
    Quit,
}


pub fn get_recv_channel() -> Receiver<Message> {
    let mut bus = BUS.lock().unwrap();
    let r = bus.claim();
    r.unwrap()
}

pub fn get_send_channel() -> Sender<Message> {
    let bus = BUS.lock().unwrap();
    bus.get_sender()
}
