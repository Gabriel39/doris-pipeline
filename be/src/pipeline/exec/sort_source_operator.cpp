// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#include "sort_source_operator.h"

#include "vec/exec/vsort_node.h"

namespace doris::pipeline {

SortSourceOperatorTemplate::SortSourceOperatorTemplate(int32_t id, const string& name,
                                                       vectorized::VSortNode* sort_node,
                                                       std::shared_ptr<SortContext> sort_context)
        : OperatorTemplate(id, name, sort_node),
          _sort_node(sort_node),
          _sort_context(sort_context) {}

SortSourceOperator::SortSourceOperator(SortSourceOperatorTemplate* operator_template,
                                       vectorized::VSortNode* sort_node,
                                       std::shared_ptr<SortContext> sort_context)
        : Operator(operator_template), _sort_node(sort_node), _sort_context(sort_context) {}

Status SortSourceOperator::init(const doris::ExecNode* node, doris::RuntimeState* state) {
    RETURN_IF_ERROR(Operator::init(node, state));
    return Status::OK();
}

Status SortSourceOperator::open(doris::RuntimeState* state) {
    RETURN_IF_ERROR(Operator::open(state));
    return Status::OK();
}

Status SortSourceOperator::close(doris::RuntimeState* state) {
    if (is_closed()) {
        return Status::OK();
    }
    return Operator::close(state);
}

Status SortSourceOperator::get_block(RuntimeState* state, vectorized::Block* block, bool* eos) {
    return _sort_node->get_sorter()->get_next(state, block, eos);
}

} // namespace doris::pipeline