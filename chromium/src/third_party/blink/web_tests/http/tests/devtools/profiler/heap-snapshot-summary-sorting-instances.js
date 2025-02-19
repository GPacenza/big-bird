// Copyright 2017 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

import {TestRunner} from 'test_runner';
import {HeapProfilerTestRunner} from 'heap_profiler_test_runner';

(async function() {
  TestRunner.addResult(`Tests sorting in Summary view of detailed heap snapshots.\n`);
  await TestRunner.showPanel('heap-profiler');

  var instanceCount = 10;
  function createHeapSnapshot() {
    return HeapProfilerTestRunner.createHeapSnapshot(instanceCount);
  }

  HeapProfilerTestRunner.runHeapSnapshotTestSuite([function testSorting(next) {
    HeapProfilerTestRunner.takeAndOpenSnapshot(createHeapSnapshot, step1);

    function step1() {
      HeapProfilerTestRunner.switchToView('Summary', step1a);
    }

    var columns;
    var currentColumn;
    var currentColumnOrder;

    function step1a() {
      var row = HeapProfilerTestRunner.findRow('B');
      TestRunner.assertEquals(true, !!row, '"B" row');
      HeapProfilerTestRunner.expandRow(row, step2);
    }

    function step2(row) {
      columns = HeapProfilerTestRunner.viewColumns();
      currentColumn = 0;
      currentColumnOrder = false;
      step3();
    }

    function step3() {
      if (currentColumn >= columns.length) {
        setTimeout(next, 0);
        return;
      }

      HeapProfilerTestRunner.clickColumn(columns[currentColumn], step4);
    }

    function step4(newColumnState) {
      columns[currentColumn] = newColumnState;
      var columnName = columns[currentColumn].id;
      var row = HeapProfilerTestRunner.findRow('B');
      TestRunner.assertEquals(true, !!row, '"B" row');
      var contents = row.children.map(function(obj) {
        return obj.element().children[currentColumn].textContent;
      });
      TestRunner.assertEquals(instanceCount, contents.length, 'column contents');
      var sortTypes = {object: 'text', distance: 'number', count: 'number', shallowSize: 'size', retainedSize: 'size'};
      TestRunner.assertEquals(true, !!sortTypes[columns[currentColumn].id], 'sort by id');
      HeapProfilerTestRunner.checkArrayIsSorted(
          contents, sortTypes[columns[currentColumn].id], columns[currentColumn].sort);

      if (!currentColumnOrder)
        currentColumnOrder = true;
      else {
        currentColumnOrder = false;
        ++currentColumn;
      }
      step3();
    }
  }]);
})();
