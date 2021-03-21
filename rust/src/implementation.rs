use crate::database;
use crate::interface::*;

use std::ops::Index;

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

type EntryModelItem = database::Entry;

pub struct EntryModel {
    emit: EntryModelEmitter,
    model: EntryModelTree,
    list: database::Entries,
}

impl EntryModelTrait for EntryModel {
    fn new(emit: EntryModelEmitter, model: EntryModelTree) -> EntryModel {
        EntryModel {
            emit,
            model,
            list: database::get_entries(),
        }
    }
    fn emit(&mut self) -> &mut EntryModelEmitter {
        &mut self.emit
    }
    fn row_count(&self, item: Option<usize>) -> usize {
        self.list.len()
    }
    fn index(&self, item: Option<usize>, row: usize) -> usize {
        0
    }
    fn parent(&self, index: usize) -> Option<usize> {
        None
    }
    fn row(&self, index: usize) -> usize {
        index
    }
    fn check_row(&self, index: usize, _row: usize) -> Option<usize> {
        if index < self.list.len() {
            Some(index)
        } else {
            None
        }
    }
    fn description(&self, index: usize) -> String {
        self.list.index(index).description.clone()
    }
    fn duration(&self, index: usize) -> u32 {
        self.list.index(index).duration as u32
    }
    fn start(&self, index: usize) -> String {
       self.list.index(index).start.clone()
    }
}
