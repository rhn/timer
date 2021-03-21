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
        row
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
    fn customer(&self, index: usize) -> &str {
       self.list.index(index).customer.as_str()
    }
    fn add(&mut self, duration: u32, description: String, customer: String) {
        self.list.add_entry(duration, description, customer);
        self.model.data_changed(0, self.list.len());
    }
}


pub struct CustomersModel {
    emit: CustomersModelEmitter,
    model: CustomersModelList,
    list: database::Customers,
}

impl CustomersModelTrait for CustomersModel {
    fn new(emit: CustomersModelEmitter, model: CustomersModelList) -> CustomersModel {
        CustomersModel {
            emit,
            model,
            list: database::get_customers(),
        }
    }
    fn emit(&mut self) -> &mut CustomersModelEmitter {
        &mut self.emit
    }
    fn row_count(&self) -> usize {
        self.list.len()
    }
    fn name(&self, index: usize) -> &str {
        &self.list[index]
    }
}
