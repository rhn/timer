use crate::interface::*;

pub struct Log {
    emit: LogEmitter,
    day_total: u64,
}

impl LogTrait for Log {
    fn new(emit: LogEmitter) -> Log {
        Log {
            emit: emit,
            day_total: 101,
        }
    }
    fn emit(&mut self) -> &mut LogEmitter {
        &mut self.emit
    }
    fn day_total(&self) -> u64 {
        self.day_total
    }
}

